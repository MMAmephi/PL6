#include "Interface.h"

Interface::Interface() : screen(nullptr){}

Interface::Interface(WINDOW* _screen){
	screen = _screen;
	std::vector<std::string> main_choices = {"Play", "Records", "Rules", "Quit"};
	int x, y;
	getmaxyx(screen, y, x);
	Menu _main(main_choices, main_choices.size()+2, 20, (y-main_choices.size()+2)/2, (x-20)/2);
	main_menu = _main;

	std::vector<std::string> size_choices = {"4x4", "9x9", "16x16", "Back"};
	Menu _size(size_choices, size_choices.size()+2, 20, (y-size_choices.size()+2)/2, (x-20)/2);
	size_menu = _size;

	std::vector<std::string> diff_choices = {"Beginner", "Easy", "Normal", "Hard", "Expert", "Crazy","Back"};
	Menu _diff(diff_choices, diff_choices.size()+2, 20, (y-size_choices.size()+2)/2, (x-20)/2);
	diff_menu = _diff;
}


int Interface::showMenu(Menu& _menu){
	cbreak();
	refresh();

	WINDOW* menuwin = subwin(screen, _menu.y_size, _menu.x_size, _menu.y_loc, _menu.x_loc);
	box(menuwin, 0, 0);
	wborder(menuwin, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(menuwin);
	
	keypad(menuwin, true);
	int choice;
	int highlight = 0;
	while(1){
		for(int i = 0; i < _menu.choices.size(); ++i){
			if(i == highlight){
				wattron(menuwin, A_REVERSE);
			}
			mvwprintw(menuwin, i+1, 1, _menu.choices[i].c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice){
			case KEY_UP:
			case 'w':
				highlight--;
				if(highlight == -1){
					highlight = 0;
				}
				break;
			case KEY_DOWN:
			case 's':
				highlight++;
				if(highlight == _menu.choices.size()){
					highlight = _menu.choices.size()-1;
				}
				break;
			default:
				break;
		}
		if(choice == 10){
			break;
		}	
	}
	clear();
	refresh();
	return highlight;
}

int Interface::showMain(){
	clear();
	return showMenu(main_menu);
}

int Interface::showSize(){
	mvwprintw(screen, size_menu.y_loc-1, size_menu.x_loc, "Choose the board size");
	return showMenu(size_menu);	
}

int Interface::showDiff(){
	mvwprintw(screen, diff_menu.y_loc-1, diff_menu.x_loc, "Choose the difficulty");
	return showMenu(diff_menu);	
}

WINDOW* Interface::getWin(){
	return screen;
}

void Interface::showMessage(const std::string& message){
	int x, y;
	getmaxyx(screen, y, x);

	WINDOW* pan = subwin(screen, 5, 34, (y-5)/2, (x-34)/2);
	box(pan, 0, 0);
	wborder(pan, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(pan);
	mvwprintw(pan, 1, 1, message.c_str());
	mvwprintw(pan, 3, 1, "Press any key to close");
	wrefresh(pan);
	wgetch(pan);
	clear();
}

void Interface::showEnd(std::time_t _time, int _score, int _mistakes,int _hints){
	int x, y;
	getmaxyx(screen, y, x);

	WINDOW* pan = subwin(screen, 12, 50, (y-12)/2, (x-50)/2);
	box(pan, 0, 0);
	wborder(pan, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(pan);
	mvwprintw(pan, 1, 1, "Congratulations! You've done it!");
	mvwprintw(pan, 3, 1, "Run info:");
	mvwprintw(pan, 4, 1, "Time %d", _time);
	mvwprintw(pan, 5, 1, "Score %d", _score);
	mvwprintw(pan, 6, 1, "Used hints %d", _mistakes);
	mvwprintw(pan, 7, 1, "Mistakes %d", _hints);
	mvwprintw(pan, 9, 1, "Press 's' to save result");
	mvwprintw(pan, 10, 1, "Press any other key to close without saving");
	wrefresh(pan);
	wgetch(pan);
	clear();
}

std::string Interface::hex(const int num){
	switch(num){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			return std::to_string(num);
		case 10:
			return "A";
		case 11:
			return "B";
		case 12:
			return "C";
		case 13:
			return "D";
		case 14:
			return "E";
		case 15:
			return "F";
		case 16:
			return "G";
		default:
			return "0";
	}
}

std::pair<int, std::pair<int, int>> Interface::showGrid(Grid& board, std::pair<int, int>& curr_pos){
	cbreak();
	refresh();

	int grid_size = board.getSize()*board.getSize();
	int y_loc, x_loc;
	getmaxyx(screen, y_loc, x_loc);

	WINDOW* gridwin = subwin(screen, grid_size+board.getSize()+1, 2*grid_size+1, (y_loc-grid_size)/2, (x_loc-2*grid_size)/2);
	box(gridwin, 0, 0);
	wborder(gridwin, 124, 124, 45, 45, 43, 43, 43, 43);

	keypad(gridwin, true);
	int choice;
	std::pair<int, int> highlight;
	highlight = std::make_pair(curr_pos.first, curr_pos.second);

	std::pair<int, std::pair<int, int>>  prev;
	int end = 0;

	while(1){
		for(int i = 0; i < grid_size; ++i){
			for(int j = 0; j < grid_size; ++j){
				wmove(gridwin, 0, 0);
				if(i == highlight.first && j== highlight.second){
					wattron(gridwin, A_REVERSE);
				}

				if(board[i][j] == 0){
					mvwprintw(gridwin, i+i/board.getSize()+1, 2*j+1, " ");
				}
				else{
					mvwprintw(gridwin, i+i/board.getSize()+1, 2*j+1, hex(board[i][j]).c_str());
				}
				wattroff(gridwin, A_REVERSE);

				if(j%board.getSize()==0 && j>0){
					mvwprintw(gridwin, i+i/board.getSize()+1, 2*j, "|");
				}
				if(i%(board.getSize()+1)==0 && i>0){
					mvwprintw(gridwin, i, 2*j+1, "-");
					if(2*(j+1) < 2*grid_size){
						mvwprintw(gridwin, i, 2*(j+1), "-");
					}
					if(j%board.getSize()==0 && j>0){
						mvwprintw(gridwin, i, 2*j, "+");
					}
				}
			}
		}
		choice = wgetch(gridwin);

		switch(choice){
			case KEY_UP:
				highlight.first--;
				if(highlight.first == -1){
					highlight.first = 0;
				}
				break;
			case KEY_DOWN:
				highlight.first++;
				if(highlight.first == grid_size){
					highlight.first = grid_size-1;
				}
				break;
			case KEY_LEFT:
				highlight.second--;
				if(highlight.second == -1){
					highlight.second = 0;
				}
				break;
			case KEY_RIGHT:
				highlight.second++;
				if(highlight.second == grid_size){
					highlight.second = grid_size -1;
				}
				break;
			default:
				prev = std::make_pair(choice-'0', highlight);
				end = 1;
				break;
		}
		if(end == 1){
			break;
		}
	}
	clear();
	refresh();
	return prev;
}

void Interface::showRules(){
	int x, y;
	getmaxyx(screen, y, x);

	WINDOW* rules = subwin(screen, 20, 70, (y-20)/2, (x-70)/2);
	box(rules, 0, 0);
	wborder(rules, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(rules);
	mvwprintw(rules, 1, 32, "Rules");
	mvwprintw(rules, 2, 1, "*The playing field is a square of n^2xn^2.");
	mvwprintw(rules, 3, 1, "*You can only enter numbers from 1 to n^2.");
	mvwprintw(rules, 4, 1, "*Each nxn block contains each number from 1 to n^2.");
	mvwprintw(rules, 5, 1, "*Each column also contains each number from 1 to n^2.");
	mvwprintw(rules, 6, 1, "*Each line also contains each number from 1 to n^2.");
	mvwprintw(rules, 7, 1, "*Each number can appear in block, column or line only once.");
	mvwprintw(rules, 8, 1, "*As soon as you fill the board the game is over.");
	mvwprintw(rules, 10, 27, "Additional info");
	mvwprintw(rules, 11, 1, "*In 16x16 mode use signs A,B,C,D,E,F,G as numbers.");
	mvwprintw(rules, 12, 1, "*Amount of hints, limit of mistakes depend on the difficulty.");
	mvwprintw(rules, 13, 1, "*The score depends on the difficulty. Extra points for combo.");
	mvwprintw(rules, 18, 1, "Press any key to go back to main menu");
	wrefresh(rules);
	wgetch(rules);
	clear();
}

void Interface::showrecords(Leaderboard& _records){
	int x, y;
	getmaxyx(screen, y, x);
	
	std::vector<PlayerRecord> records = _records.getRecords();

	WINDOW* rec = subwin(screen, records.size()+2, 70, (y-records.size()-2)/2, (x-70)/2);
	box(rec, 0, 0);
	wborder(rec, 124, 124, 45, 45, 43, 43, 43, 43);
	wrefresh(rec);
	for(int i = 0; i < records.size(); ++i){
		mvwprintw(rec, i+1, 1, records[i].playerName.c_str()+"%d.%d.%d %d:%d:%d );
	
	}
}
