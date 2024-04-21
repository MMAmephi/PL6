#include "Generator.h"

template <class T>
Generator<T>::Generator():baseGrid(){};

template <class T>
Generator<T>::Generator(int _size){
    Grid tmp(_size);
    baseGrid = tmp;
    linet nums(baseGrid.getSize()*baseGrid.getSize());
    for(int i = 0; i < nums.size(); ++i){
        nums[i] = i+1;
    }
    int pos = 0;
    for(int i = 0; i < _size*_size; ++i){
        for(int j = 0; j < _size*_size; ++j){
            baseGrid.change(i, j, nums[pos%(_size*_size)]);
            pos++;
        }
        pos = ((i+1)%_size)*_size + ((i+1)/_size);
    }
}

template <class T>
Generator<T>::Generator(Grid board) : Generator<T>::Generator(board.getSize()){};

template <class T>
bool Generator<T>::checkBoard(const Grid& board){
    Grid ans1 = solver.solve(board);
    Grid t_board = board;
    Grid ans2 = solver.solve(t_board.transposing());
    if(ans1 == board){
        return false;
    }
    else{
        return true;
    }
}

/*
Grid Generator::genGrid(int erase_num){
    Grid board = baseGrid;
    board = board.mix();

    srand(time(0));
    while(erase_num > 0) {
        int row = rand() % (board.getSize()*board.getSize());
        int col = rand() % (board.getSize()*board.getSize());
        if (board[row][col] != 0) {
            int temp = board[row][col];
            board.change(row, col, 0);
            if (checkBoard(board)){
                //std::cout << erase_num << std::endl;
                //board.printGrid();
                erase_num--;
            } 
            else{
                board.change(row, col, temp);
            }
        }
    }
    return board;
}
*/

template <class T>
void Generator<T>::shuffle(std::vector<std::pair<int, int>>& vec) {
    std::mt19937 rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, vec.size() - 1);
    int random_index;
    for (int i = 0; i < vec.size(); ++i) {
        random_index = dist(rng);
        std::swap(vec[i], vec[random_index]);
    }
}

template <class T>
Grid Generator<T>::genGrid(int erase_num){
    Grid board = baseGrid;

    std::vector<std::pair<int, int>> nums(pow(board.getSize(), 4));
    for(int i = 0; i < pow(board.getSize(), 2); ++i){
        for(int j = 0; j < pow(board.getSize(), 2); ++j){
            nums[i*pow(board.getSize(), 2) + j] = std::make_pair(i, j);
        }
    }
    shuffle(nums);
    int step;
    int row, col, temp;
    int erased;
    while(erase_num != erased){
	board = baseGrid;
	board = board.mix();
	//board.printGrid();
	erased = 0;
	step = 0;
	while(erased != erase_num && step < nums.size()) {
        	row = nums[step].first;
        	col = nums[step].second;
        	temp = board[row][col];
        	board.change(row, col, 0);
        	if (checkBoard(board)){
            		//std::cout << step << " " << erased << std::endl;
            		//board.printGrid();
            		erased++;
        	} 
        	else{
            		board.change(row, col, temp);
        	}
        	step++;
    	}
	break;
    }
    return board;
}

template <class T>
Grid Generator<T>::solveGrid(const Grid& board){
	return solver.solve(board);
}
