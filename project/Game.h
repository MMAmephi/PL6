#ifndef GAME
#define GAME

#include "Interface.h"
#include "Generator.h"
#include "Leaderboard.h"

#include<experimental/filesystem>
#include <ctime>

namespace fs = std::experimental::filesystem;

struct GameSettings{
	int boardSize;
	int difficulty;
	int maxMistakes;
	int maxHints;

	GameSettings();
      	GameSettings(int _size, int _diff, int _mistakes, int _hints);
};

struct SessionInfo{
	int score;
	std::time_t time_s;
	std::time_t time_prev;
	int mistakesDone;
	int hintsUsed;

	SessionInfo();
	SessionInfo(int _score, int _mistakes, int _hints);
	void setToZero();
};

class Game{
private:
	GameSettings settings;
	SessionInfo info;
	Interface gameint;
	Generator<OptimisedSearch> gen;
	std::string problems_path = ".problems";
	int combo_limit = 3;

	std::vector<std::pair<int, int>> levels;

public:
	Game();
	void game();
	void session();
	void setSettings(int _size, int _diff);
	void setGen();
	void refresh(int num_levels = 3);
	int countScore(Grid& board, std::pair<int, std::pair<int, int>> move, bool mistake);
	std::tm* getCurrentTime();
};

#endif
