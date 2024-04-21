#ifndef INTERFACE
#define INTERFACE

#include "Grid.h"
#include <ncurses.h>
#include <vector>
#include <string>

struct Menu{
	std::vector<std::string> choices;
	int y_size;
	int x_size;
	int y_loc;
	int x_loc;
	
	Menu() :  y_size(0), x_size(0), y_loc(0), x_loc(0){};
	Menu(std::vector<std::string> _ch, int _y_s, int _x_s, int _y_l, int _x_l) : choices(_ch), y_size(_y_s), x_size(_x_s), y_loc(_y_l), x_loc(_x_l){};
};

class Interface{
private:
	WINDOW* screen;
	Menu main_menu;
	Menu size_menu;
	Menu diff_menu;
public:
	Interface();
	Interface(WINDOW*);

	int showMenu(Menu& _menu);
	int showMain();
	int showSize();
	int showDiff();

	WINDOW* getWin();
	std::string hex(const int num);

	void showMessage(const std::string& message);

	std::pair<int, std::pair<int, int>> showGrid(Grid& board, std::pair<int, int>& curr_pos);
	void showRules();
	void showRecords(LeaderBoard& records);
	void showEnd(std::time_t _time, int _score, int _mistakes, int _hints);
};



#endif
