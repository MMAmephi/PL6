#include "Leaderboard.h"
#include <ctime>

PlayerRecord::PlayerRecord() : playerName("Unknown"), boardSize(0), difficulty(0), score(0), time_spent(std::time(0)), mistakes(0), hints(0){
	std::time_t t = std::time(0);
	date = std::localtime(&t);
}

PlayerRecord::PlayerRecord(std::string _name,std::tm* _date, int _size, int _diff, int _score, std::time_t _time, int _mistakes, int_hints) : playerName(_name), boardSize(_size), difficulty(_diff), score(_score), time_spent(_time), mistakes(_mistakes), hints(_hints){
	std::time_t t = std::time(0);
	date = std::localtime(&t);
}

std::vector<PlayerRecord> Leaderboard::getrecords(){
	return records;
}

void Leaderboard::addRecord(PlayerRecord record){
	records.push_back(record);
}
