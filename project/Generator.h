#ifndef GEN
#define GEN
#include "Grid.h"
#include "OptimisedSearch.h"
#include "CompleteSearch.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <cmath>

template <class T>
class Generator{
public:
    Grid baseGrid;
    T solver;

    void shuffle(std::vector<std::pair<int, int>>& vec);
public:
    Generator();

    Generator(int _size);

    Generator(Grid board);

    bool checkBoard(const Grid& board);

    Grid genGrid(int erase_num);

    Grid solveGrid(const Grid& board);
};
#endif
