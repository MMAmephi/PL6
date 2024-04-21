#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <experimental/filesystem>
#include <cstring>
#include <vector>
#include <algorithm>

namespace fs = std::experimental::filesystem;

class VersionControl {
private:
    std::string baseDir = ".vcon";
    std::string logFile = ".vcon/log.txt";
    std::string extendedLogFile = ".vcon/extended_log.txt";
    std::string trackedFiles = ".vcon/trackedFiles.txt";

    std::string getCurrentTime() {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return buffer;
    }

    void writeLog(const std::string& message) {
        std::ofstream logfile(logFile, std::ios::app);
        logfile << getCurrentTime() << ": " << message << std::endl;
        logfile.close();
    }

    void writeExtendedLog(const std::string& message) {
        std::ofstream logfile(extendedLogFile, std::ios::app);
        logfile << getCurrentTime() << ": " << message << std::endl;
        logfile.close();
    }

public:
    VersionControl(){};

    std::string get_trackedFiles(){
	    return trackedFiles;
    }

    std::string get_logFile(){
	    return logFile;
    }

    std::string get_extendedLogFile(){
	    return extendedLogFile;
    }

    bool check_init(){
	    return fs::exists(baseDir);
    }

    void init(){
	if(fs::exists(baseDir)){
		std::cerr << "Already initialised" << std::endl;
		writeLog("Unsuccessful initialisation of version control system. Already initialised");
        	writeExtendedLog("Unsuccessful initialisation of version control system. Already initialised");

        }
	else{
		fs::create_directory(baseDir);
		writeLog("Initialised version control system");
        	writeExtendedLog("Initialised version control system");
	}
    }

    void add(const std::string& file) {
        fs::path filePath = baseDir + "/" + file;
        fs::path currentDir = fs::current_path();
        fs::path sourceFile = currentDir / file;
        if (!fs::exists(sourceFile)){
            std::cerr << "File " << file << " not found" << std::endl;
            writeLog("Unsuccessful attempt to add " + file + " File not found");
            writeExtendedLog("Unsuccessful attempt to add " + file +" File not found");
        } else if(fs::exists(filePath)){
            std::cerr << "File " << file << " already added" << std::endl;
            writeLog("Unsuccessful attempt to add " + file + " Already added");
            writeExtendedLog("Unsuccessful attempt to add " + file +" Already added");
        }
        else{
            fs::create_directory(filePath);
            std::ofstream tracked(trackedFiles, std::ios::app);
            tracked << file << std::endl;
            writeLog("Added file " + file);
            writeExtendedLog("Added file " + file);
        }
    }

    void remove(const std::string& file) {
        fs::path filePath = baseDir + "/" + file;
        if (fs::exists(filePath)) {
            fs::remove_all(filePath);

            std::ifstream tracked(trackedFiles);
            std::string line;
            std::vector<std::string> curr_tracked;
            while(std::getline(tracked, line)){
                curr_tracked.push_back(line);
            }
            curr_tracked.erase(find(curr_tracked.begin(), curr_tracked.end(), file));
            std::ofstream new_tracked(trackedFiles);
            for(int i = 0; i < curr_tracked.size(); i++){
                new_tracked << curr_tracked[i] << std::endl;
            }
            writeLog("Removed file " + file);
            writeExtendedLog("Removed file " + file);
        }
        else{
            std::cerr << "File " << file << " not found" << std::endl;
            writeLog("Unsuccessful attempt to remove " + file + " File not found");
            writeExtendedLog("Unsuccessful attempt to remove " + file +" File not found");
        }
    }

    void fix(const std::string& file) {
        fs::path filePath = baseDir + "/" + file;
        fs::path currentDir = fs::current_path();
        fs::path sourceFile = currentDir / file;

        if (!fs::exists(sourceFile)){
            std::cerr << "File " << file << " not found" << std::endl;
            writeLog("Unsuccessful attempt to fix " + file + " File not found");
            writeExtendedLog("Unsuccessful attempt to fix " + file +" File not found");
        }
        else if (fs::exists(filePath)) {
            int version = 1;
            for (const auto& entry : fs::directory_iterator(filePath)) {
                if (std::isdigit(entry.path().stem().string()[0])) {
                    int num = std::stoi(entry.path().stem().string());
                    version = std::max(version, num + 1);
                }
            }

            writeExtendedLog("Fixed version " + std::to_string(version) + " of file " + file);
            if (version > 1) {
                fs::path prevVersionFile = filePath / (std::to_string(version - 1) + ".cpp");
                std::ifstream prevFile(prevVersionFile);
                std::ifstream newFile(sourceFile);
                std::stringstream diffStream;

                std::string line1, line2;
                while (std::getline(prevFile, line1) && std::getline(newFile, line2)) {
                    if (line1 != line2) {
                        diffStream << "- " << line1 << std::endl;
                        diffStream << "+ " << line2 << std::endl;
                    }
                }

                prevFile.close();
                newFile.close();

                if (!diffStream.str().empty()) {
                    writeExtendedLog("Changes in version " + std::to_string(version) + " of file " + file + "\n" +diffStream.str());
                }
            }

            fs::path versionFile = filePath / (std::to_string(version) + ".cpp");
            fs::copy_file(sourceFile, versionFile);

            writeLog("Fixed version " + std::to_string(version) + " of file " + file);
        }
        else{
            std::cerr << "File " << file << " not added to version control" << std::endl;
            writeLog("Unsuccessful attempt to fix " + file + " File not added to version control");
            writeExtendedLog("Unsuccessful attempt to fix " + file +" File not added to version control");
        }
    }

    void diff(const std::string& file, int version1 = 0, int version2 = 0) {
        fs::path filePath = baseDir + "/" + file;
        if (!fs::exists(filePath)) {
            std::cerr << "File not found." << std::endl;
            return;
        }

        int latestVersion = 0;
        for (const auto& entry : fs::directory_iterator(filePath)) {
            if (std::isdigit(entry.path().stem().string()[0])) {
                int num = std::stoi(entry.path().stem().string());
                latestVersion = std::max(latestVersion, num);
            }
        }

        if (version2 == 0) {
            version2 = latestVersion;
        }

        if (version2 > latestVersion) {
            std::cerr << "Such version doesn't exist" << std::endl;
            return;
        }

        if (version1 == version2) {
            std::cerr << "Versions are the same" << std::endl;
            return;
        }

        fs::path currentDir = fs::current_path();
        fs::path file1 = currentDir / file;
        if(version1 != 0){
            file1 = filePath / (std::to_string(version1) + ".cpp");
        }

        fs::path file2 = filePath / (std::to_string(version2) + ".cpp");

        std::ifstream infile1(file1);
        std::ifstream infile2(file2);
        std::string line1, line2;
        int lineNumber = 1;

        while (std::getline(infile1, line1) && std::getline(infile2, line2)) {
            if (line1 != line2) {
                std::cout << "Difference at line " << lineNumber << std::endl;
                std::cout << "- " << line1 << std::endl;
                std::cout << "+ " << line2 << std::endl;
            }
            lineNumber++;
        }

        while (std::getline(infile1, line1)) {
            std::cout << "- " << line1 << std::endl;
            lineNumber++;
        }

        while (std::getline(infile2, line2)) {
            std::cout << "+ " << line2 << std::endl;
            lineNumber++;
        }

        infile1.close();
        infile2.close();
    }

    void step(const std::string& file, int version = 0) {
        fs::path filePath = baseDir + "/" + file;
        if (!fs::exists(filePath)) {
            std::cerr << "File not found" << std::endl;
            return;
        }

        if (version == 0) {
            int latestVersion = 0;
            for (const auto& entry : fs::directory_iterator(filePath)) {
                if (std::isdigit(entry.path().stem().string()[0])) {
                    int num = std::stoi(entry.path().stem().string());
                    latestVersion = std::max(latestVersion, num);
                }
            }
            version = latestVersion;
        }

        fs::path currentDir = fs::current_path();
        fs::path sourceFile = currentDir / file;
        fs::path versionFile = filePath / (std::to_string(version) + ".cpp");

        if (fs::exists(versionFile)) {
            fs::remove(sourceFile);
            fs::copy_file(versionFile, sourceFile);
            writeLog("Reverted " + file + " to version " + std::to_string(version));
            writeExtendedLog("Reverted " + file + " to version " + std::to_string(version));
        } else {
            std::cerr << "Version not found." << std::endl;
            writeLog("Unsuccessful attempt to revert " + file + " to version " + std::to_string(version) + " File not found");
            writeExtendedLog("Unsuccessful attempt to revert " + file + " to version " + std::to_string(version) + " File not found");
        }
    }

    void showLog(const std::string& Log){
        std::ifstream infile(Log);
        std::string line;
        while(std::getline(infile, line)){
            std::cout << line << std::endl;
        }
    }

    void showhelp(){
        std::cout << "\t\tinit - initialise version control system\n\
		add <filename1> [filename2 ...] - make files be tracked\n\
		remove <filename1> [filename2 ...] - stop files being tracked\n\
		fix [filename1 ...] - fix version of file\n\
		diff <filename> [version1] [version2] - show the difference between version1 and version2 of file\n\
		step <filename> [version] - turn file into its version (if not mentioned, latest version)\n\
		log - show all done actions\n\
		extendedlog - same as log, but also show changes in files during fixes\n\
		tracked - show the list of tracked files\n\
		help - show all possible commands\n" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    VersionControl vcon;

    if (argc < 2) {
        std::cerr << "Try " << argv[0] << " 'help' to see possible commands" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    if(command == "help"){
        vcon.showhelp();
        return 0;
    } else if (command == "init") {
        vcon.init();
        return 0;
    } else if (command == "tracked"){
	    std::ifstream tracked(vcon.get_trackedFiles());
	    std::string line;
	    while(std::getline(tracked, line)){
		    std::cout << line << std::endl;
	    }
	    return 0;
    }


    if(vcon.check_init()){ 
	if(command == "log"){
        	vcon.showLog(vcon.get_logFile());
        	return 0;
    	} else if(command == "extendedlog"){
        	vcon.showLog(vcon.get_extendedLogFile());
        	return 0;
    	} else if (command == "fix") {
        	if(argc > 2){
            		for(int i = 2; i < argc; i++){
                		vcon.fix(argv[i]);
            		}
        	}
        	else{
            		std::ifstream tracked(vcon.get_trackedFiles());
            		std::string line;
            		while(std::getline(tracked, line)){
                		vcon.fix(line);
            		}
        	}
        	return 0;
    	}

    	if(argc < 3){
        	std::cerr << "Invalid command or insufficient arguments. Try 'help' to see possible commands" << std::endl;
        	return 1;
    	}

    	if (command == "add") {
        	for(int i = 2; i < argc; i++){
            		vcon.add(argv[i]);
        	}
    	} else if (command == "remove") {
        	for(int i = 2; i < argc; i++){
            		vcon.remove(argv[i]);
        	}
    	} else if (command == "diff") {
        	if (argc >= 5) {
            		int version1 = std::stoi(argv[3]);
            		int version2 = std::stoi(argv[4]);
            		vcon.diff(argv[2], version1, version2);
        	} else if(argc == 4){
            		vcon.diff(argv[2], std::stoi(argv[3]), 0);
        	} 
        	else {
            		vcon.diff(argv[2]);
        	}
    	} else if (command == "step") {
        	if (argc >= 4) {
            		int version = std::stoi(argv[3]);
            		vcon.step(argv[2], version);
        	} else {
            		vcon.step(argv[2]);
        	}
    	} else {
        	std::cerr << "Invalid command or insufficient arguments. Try 'help' to see possible commands" << std::endl;
        	return 1;
    	}
    }
    else{
	    std::cerr << "Version control system wasn't initialized" << std::endl;
    }
    return 0;
}
