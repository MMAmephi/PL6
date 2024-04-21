#include "OptimisedSearch.h"

linet OptimisedSearch::findPossibleValues(Grid& board, int row, int col){
    linet possible;
    for(int i = 0; i < board.getSize()*board.getSize(); ++i){
        possible.push_back(i+1);
    }
    for(int el:board.getColValues(col)){
        possible.erase(std::remove(possible.begin(), possible.end(), el), possible.end());
    }
    for(int el:board.getRowValues(row)){
        possible.erase(std::remove(possible.begin(), possible.end(), el), possible.end());
    }
    gridt temp = board.getBlockValues(row/board.getSize(), col/board.getSize());
    for(int i = 0; i < board.getSize(); ++i){
        for(int j = 0; j < board.getSize(); ++j){
            possible.erase(std::remove(possible.begin(), possible.end(), temp[i][j]), possible.end());
        }
    }
    return possible;
}

bool OptimisedSearch::isFinished(Grid& board){
    for(int row = 0; row < board.getSize()*board.getSize(); ++row){
        for(int col = 0; col < board.getSize()*board.getSize(); ++col){
            if(board[row][col] == 0){
                return false;
            }
        }
    }
    return true;
}

bool OptimisedSearch::backtrack(Grid& board) {
    for (int row = 0; row < board.getSize()*board.getSize(); ++row) {
        for (int col = 0; col < board.getSize()*board.getSize(); ++col) {
            if (board[row][col] == 0) {
                linet possibleValues = findPossibleValues(board, row, col);
                if (possibleValues.empty()) {
                    return false;
                }
                for (int val : possibleValues) {
                    board.change(row, col, val);
                    if (backtrack(board)) {
                        return true;
                    }
                    board.change(row, col, 0);
                }
                return false;
            }
        }
    }
    return true;    
}

Grid OptimisedSearch::solve(const Grid& board){
    Grid ans = board;
    if(backtrack(ans)){
        return ans;
    }
    else{
        //std::cerr << "There is no solution" << std::endl;
        return ans;
    }
} 
