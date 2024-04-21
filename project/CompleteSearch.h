#ifndef COMPLETE
#define COMPLETE

#include "Grid.h"

class CompleteSearch{
private:
    bool isCorrect(Grid& board, int row, int col, int num);

    bool findEmptyPosition(Grid& board, int& row, int& col);

    bool backtrack(Grid& board);

public:
    Grid solve(const Grid& board);  
};
#endif
