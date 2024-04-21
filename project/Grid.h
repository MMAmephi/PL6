#ifndef GRID
#define GRID

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using gridt = std::vector<std::vector<int>>;
using linet = std::vector<int>;  

class Grid{
private:
    int gridSize;
    gridt values;
public:
    Grid();

    Grid(int _gridSize);

    Grid(int _gridSize, gridt _values);

    Grid(const Grid& other);

    Grid(std::string filename);

    ~Grid();

    int getSize();

    gridt getValues();

    Grid transposing();

    Grid swap_rows(int row1, int row2);

    Grid swap_cols(int col1, int col2);

    Grid swap_row_area(int area1, int area2);

    Grid swap_col_area(int area1, int area2);

    Grid mix();

    void change(int i, int j, int _value);

    linet getRowValues(int _row);

    linet getColValues(int _col);

    gridt getBlockValues(int _row, int _col);

    bool isRowFinished(int r);

    bool isColFinished(int c);

    bool isBlockFinished(int _r, int _c);
    
    linet operator[](int i);

    bool operator==(const Grid& other);

    void write(std::string file_out);

    void printGrid();
};

#endif
