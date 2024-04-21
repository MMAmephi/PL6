#include "Game.h"

GameSettings::GameSettings() : boardSize(0), difficulty(0), maxMistakes(0), maxHints(0){}
      	
GameSettings::GameSettings(int _size, int _diff, int _mistakes, int _hints) : boardSize(_size), difficulty(_diff), maxMistakes(_mistakes), maxHints(_hints){};

SessionInfo::SessionInfo() : score(0), mistakesDone(0), hintsUsed(0){
	time_s = std::time(0);
	time_prev = std::time(0);
}

SessionInfo::SessionInfo(int _score, int _mistakes, int _hints) : score(_score), mistakesDone(_mistakes), hintsUsed(_hints){
	time_s  = std::time(0);
	time_prev = std::time(0);
}

void SessionInfo::setToZero(){
	score = 0;
	time_s = std::time(0);
	mistakesDone = 0;
	hintsUsed = 0;
}

Game::Game(){
	initscr();
	noecho();
	curs_set(0);

	levels.push_back(std::make_pair(5, 5));
	levels.push_back(std::make_pair(3, 3));
	levels.push_back(std::make_pair(3, 2));
	levels.push_back(std::make_pair(3, 1));
	levels.push_back(std::make_pair(3, 0));
	levels.push_back(std::make_pair(0, 0));

	Interface temp(stdscr);
	gameint = temp;
}

void Game::setSettings(int _size, int _diff){
	GameSettings temp(_size, _diff, levels[_diff].first, levels[_diff].second);
	settings = temp;
}

void Game::setGen(){
	Generator<OptimisedSearch> temp(settings.boardSize);
	gen = temp;
}

void Game::game(){
    	int choice;
    	bool end = 0;
    	while(1){
    		choice = gameint.showMain();
    		switch(choice){
    			case 0:
				clear();
				this->session();
				break;
    			case 1:
				clear();
				printw("1");
				getch();
				//gameint.showRecords();
				break;
   			case 2:
				clear();
				gameint.showRules();
				break;
   			case 3:
				end = 1;
				break;
			default:
				break;
   		}
   		if(end)
			break;
  	}
    	endwin(); 
}

std::tm* Game::getCurrentTime(){
	std::time_t t = std::time(0);
	std::tm* curr_t = std::localtime(&t);
	return curr_t;
}

void Game::session(){
	//Grid tmp("Grid2.txt");
    	//Grid board = tmp;
	
	int choice;
    	bool end = 0;
	int _size;
	int difficulty;
    	choice = gameint.showSize();
    	switch(choice){
    		case 0:
			clear();
			_size=2;
			break;
    		case 1:
			clear();
			_size=3;
			break;
   		case 2:
			clear();
			_size=4;
			break;
   		case 3:
			end = 1;
			break;
		default:
			break;
   	}
	if(end)
		return;
	else{
    		choice = gameint.showDiff();
    		switch(choice){
    			case 0:
				clear();
				difficulty=0;
				break;
    			case 1:
				clear();
				difficulty=1;
				break;
   			case 2:
				clear();
				difficulty=2;
				break;
   			case 3:
				clear();
				difficulty=3;
				break;
   			case 4:
				clear();
				difficulty=4;
				break;
			case 5:
				clear();
				difficulty=5;
				break;		
   			case 6:
				end = 1;
				break;
			default:
				break;
   		}
	}

	if(end)
		return;

	this->setSettings(_size, difficulty);
	this->setGen();
	Grid board = gen.genGrid((0.45+settings.difficulty*0.05)*pow(settings.boardSize, 4));
	Grid solution = gen.solver.solve(board);
	//Grid solution = gen.solveGrid(board);
	std::pair<int, std::pair<int, int>> move;
	std::pair<int, int> curr_pos;
	curr_pos = std::make_pair(0, 0);
	int y_max, x_max;
	getmaxyx(gameint.getWin(), y_max, x_max);
	info.time_s = std::time(0);
	while(!(board == solution)){
		mvwprintw(gameint.getWin(), 0, 0, "Mistakes: %d/%d", info.mistakesDone, settings.maxMistakes);
		mvwprintw(gameint.getWin(), 1, 0, "Hints: %d/%d", info.hintsUsed, settings.maxHints);
		mvwprintw(gameint.getWin(), 2, 0, "Score: %d", info.score);
		mvwprintw(gameint.getWin(), 3, 0, "Time: %2d:%2d", (std::time(0) - info.time_s)/60,(std::time(0) - info.time_s)%60);
		mvwprintw(gameint.getWin(), y_max-3, 0, "Use arrows to move");
		mvwprintw(gameint.getWin(), y_max-2, 0, "h - get a hint");
		mvwprintw(gameint.getWin(), y_max-1, 0, "q - quit to main menu");
		move = gameint.showGrid(board, curr_pos);
		if(info.mistakesDone == settings.maxMistakes){
			end = 1;
			break;
		}
		else if(move.first == 'q'-'0'){
			break;
		}
		else if(move.first == 'h'-'0'){
			if(info.hintsUsed < settings.maxHints){
				info.hintsUsed++;
				board.change(move.second.first, move.second.second, solution[move.second.first][move.second.second]);
			}
			else{
				gameint.showMessage("You've already used all hints");
			}	
		}
		else if(move.first > 0 && move.first <= settings.boardSize*settings.boardSize && board[move.second.first][move.second.second] == 0){
			if(move.first == solution[move.second.first][move.second.second]){
				board.change(move.second.first, move.second.second, move.first);
				info.score +=countScore(board, move, 0);
				info.time_prev = std::time(0);
			}
			else{
				info.mistakesDone++;
				info.score +=countScore(board, move, 1);
				gameint.showMessage("It's a wrong number");
			}
		}
		else{
			gameint.showMessage("Invalid input");
		}
		curr_pos = move.second;
	}
	if(board == solution){
		gameint.showEnd(std::time(0) - info.time_s, info.score, info.mistakesDone, info.hintsUsed);
	}
	else if(end){
		gameint.showMessage("OOOPS.Too many mistakes!");
	}
	info.setToZero();
}

void Game::refresh(int num_levels){
	if(!fs::exists(problems_path)){
			fs::create_directory(problems_path);
	}
	for(int i = 0; i < num_levels; i++){
		for(int _size = 2; _size <= 4; _size++){
			fs::path dirpath1 = problems_path + "/" + std::to_string(_size);
			if(!fs::exists(dirpath1)){
				fs::create_directory(dirpath1);
			}
			for(int dif = 0; dif <= 5; dif++){
				fs::path dirpath2 =  problems_path + "/" + std::to_string(_size) + "/" + std::to_string(dif);
				if(!fs::exists(dirpath2)){
					fs::create_directory(dirpath2);
				}
				fs::path filepath = problems_path + "/" + std::to_string(_size) + "/" + std::to_string(dif) + "/" + std::to_string(i);
				this->setSettings(_size, dif);
				this->setGen();
				Grid board = gen.genGrid((0.45+settings.difficulty*0.05)*pow(settings.boardSize, 4));
				board.write(filepath);
				std::cout << "completed " << i*3*6+(_size-2)*6+dif+1 << "/" << num_levels*3*6 << std::endl;
			}
		}
	}	
}

int Game::countScore(Grid& board, std::pair<int, std::pair<int, int>> move, bool mistake){
	int base = (settings.difficulty+1)*5;
	if(mistake){
		return -10*base;
	}
	else{
		if(board.isRowFinished(move.second.first)){
			base *= 5;
		}
		else if(board.isColFinished(move.second.second)){
			base *= 5;
		}
		else if(board.isBlockFinished(move.second.first/board.getSize(), move.second.second/board.getSize())){
			base *= 5;
		}
		if(std::time(0)-info.time_prev < combo_limit){
			return 2*base;
		}
		else{
			return base;
		}
	}	
}
