#ifndef OPTIM
#define OPTIM

#include <algorithm>
#include "CompleteSearch.h"

class OptimisedSearch : public CompleteSearch{
private:
    linet findPossibleValues(Grid& board, int row, int col);

    bool isFinished(Grid& board);

    bool backtrack(Grid& board);

public:
    Grid solve(const Grid& board);  
};
#endif
