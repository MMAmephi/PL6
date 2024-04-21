#include "CompleteSearch.h"

bool CompleteSearch::isCorrect(Grid& board, int row, int col, int num) {
    int n = board.getSize();
    if(board[row][col] == 0){
        for (int i = 0; i < n*n; ++i){
            if (board[row][i] == num || board[i][col] == num){
                return false;
            }
        }
        int startRow = row - row % n;
        int startCol = col - col % n;
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (board[i + startRow][j + startCol] == num){
                    return false;
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}


bool CompleteSearch::findEmptyPosition(Grid& board, int& row, int& col){
    for (row = 0; row < board.getSize()*board.getSize(); ++row) {
        for (col = 0; col < board.getSize()*board.getSize(); ++col) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool CompleteSearch::backtrack(Grid& board) {
    int row, col;
    if (!findEmptyPosition(board, row, col)) {
        return true;
    }
    for (int num = 1; num <= board.getSize()*board.getSize(); ++num) {
        if (isCorrect(board, row, col, num)) {
            board.change(row, col, num);
            if (backtrack(board)) {
                return true;
            }
            board.change(row, col, 0);
        }
    }
    return false;
}

Grid CompleteSearch::solve(const Grid& board){
    Grid ans = board;    
    if(backtrack(ans)){
        return ans;
    }
    else{
        //std::cerr << "There is no solution" << std::endl;
        return ans;
    }
}  
