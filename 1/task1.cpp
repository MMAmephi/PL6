#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

void count_pairs(string text){
       	map <string, int> pairs;
	 for(int i=0; i < text.size()-1; i++){
		 pairs[text.substr(i, 2)] =0;
	 }
	 for(int i=0; i < text.size()-1; i++){
		 pairs[text.substr(i, 2)]++;
	 }

	 map <string, int> :: iterator it = pairs.begin();
	 ofstream F;
	 F.open("results.txt");
	 for (int i = 0; it != pairs.end(); it++, i++){
		 F << it->first << ":" << it->second << endl;
	 }
	 F.close();    
}

int main(int argc, char* argv[]){	
	cout << "Choose an option:\n1)file\n2)keyboard\nEnter 1 or 2\n";
       	string ans;
       	getline(cin, ans);
       	while(ans!="1" & ans!="2"){
	       	cout << "ERROR. Choose option 1 or 2\n";
	       	getline(cin, ans);
       	}
	if(ans == "1"){
		 cout << "Enter file name" << endl;
		 string file_name;
		 getline(cin, file_name);
		 string text;
		 ifstream file;
		 file.open(file_name);
		 while(!file){
			 cout<<"This file doesn't exist. Try again\n";
			 cout<<"If you want to finish program, type 'quit'\n";
			 file.close();
			 getline(cin, file_name);
			 if(file_name=="quit"){
				 return 0;
			}
			 else{
				 file.open(file_name);
			}
		 }
		 getline(file, text);
		 count_pairs(text);
		 file.close();
	 }
	 else{
		 cout << "Enter your string" << endl;
		 string text;
		 getline(cin, text);
		 count_pairs(text);
	 }
	 return 0;
}
