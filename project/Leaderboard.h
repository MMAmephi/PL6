#ifndef LEADER
#define LEADER

struct PlayerRecord{
	std::string playerName;
	std::tm* date;
	int boardSize;
	int difficulty;
	int score;
	std::time_t time_spent;
	int mistakes;
	int hints;

	PlayerRecord();
	PlayerRecord(std::string _name,std::tm* _date, int _size, int _diff, int _score, std::time_t _time, int _mistakes, int_hints); 
};

class LeaderBoard{
private:
	std::vector<PlayerRecord> records;
public:
	std::vector<PlayerRecord> getRecords();
	//void saveToFile(std::string file_in);
	//void readFromFile(std::string file_out);
	void addRecord(PlayerRecord record);
};

#endif %
