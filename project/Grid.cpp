#include "Grid.h"

Grid::Grid(): gridSize(0){
    gridt temp(gridSize*gridSize, linet(gridSize*gridSize));
    values = temp;
}

Grid::Grid(int _gridSize): gridSize(_gridSize){
    gridt temp(_gridSize*_gridSize, linet(_gridSize*_gridSize));
    values = temp;
    for(int i = 0; i < gridSize*gridSize; i++){
        for(int j = 0; j < gridSize*gridSize; j++){
            values[i][j] = 0;
        }
    }
}

Grid::Grid(int _gridSize, gridt _values): gridSize(_gridSize){
    values = _values;
}

Grid::Grid(const Grid& other){
    gridSize = other.gridSize;
    values = other.values;
}

Grid::Grid(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> gridSize;
        gridt temp(gridSize*gridSize, linet(gridSize*gridSize));
        values = temp;
        for(int i = 0; i < gridSize*gridSize; i++){
            for(int j = 0; j < gridSize*gridSize; j++){
                file >> values[i][j];
            }
        }
        file.close();
    } 
    else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
}

Grid::~Grid(){
    for(int i = 0; i < values.size(); i++){
        values[i].clear();
    }
    values.clear();
}

int Grid::getSize(){
    return gridSize;
}

gridt Grid::getValues(){
    return values;
}

Grid Grid::transposing(){
    Grid transposed(gridSize);
    for(int i = 0; i < gridSize*gridSize; i++){
        for(int j = 0; j < gridSize*gridSize; j++){
            transposed.values[j][i] = values[i][j];
        }
    }
    return transposed;
}

Grid Grid::swap_rows(int row1, int row2){
    Grid swapped(*this);
    std::swap(swapped.values[row1], swapped.values[row2]);
    return swapped;
}

Grid Grid::swap_cols(int col1, int col2){
    Grid swapped(*this);
    for (int i = 0; i < gridSize*gridSize; i++) {
        std::swap(swapped.values[i][col1], swapped.values[i][col2]);
    }
    return swapped;
}

Grid Grid::swap_row_area(int area1, int area2){
    Grid swapped(*this);
    int start1 = area1 * gridSize;
    int start2 = area2 * gridSize;
    for (int i = 0; i < gridSize; i++) {
        std::swap(swapped.values[start1 + i], swapped.values[start2 + i]);
    }
    return swapped;
}

Grid Grid::swap_col_area(int area1, int area2){
    Grid swapped(*this);
    int start1 = area1 * gridSize;
    int start2 = area2 * gridSize;
    for (int i = 0; i < gridSize*gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            std::swap(swapped.values[i][start1 + j], swapped.values[i][start2 + j]);
        }
    }
    return swapped;
}

Grid Grid::mix(){
    int method;
    int num;
    srand(time(0));	
    for(int  i = 0; i < 100; ++i){
        method = rand()%5;
	num = rand()%(gridSize);
        switch (method) {
            case 0:
                *this = this->transposing();
                break;
            case 1:
                *this = this->swap_rows(num*gridSize + rand()%(gridSize), num*gridSize + rand()%(gridSize));
                break;
            case 2:
                *this = this->swap_cols(num*gridSize + rand()%(gridSize), num*gridSize + rand()%(gridSize));
                break;
            case 3:
                *this = this->swap_row_area(rand()%gridSize, rand()%gridSize);
                break;
            case 4:
                *this = this->swap_col_area(rand()%gridSize, rand()%gridSize);
                break;
        }
    }
    return *this;
}

void Grid::change(int i, int j, int _value){
    if(i < gridSize*gridSize && j < gridSize*gridSize){
        values[i][j] = _value;
    }
    else{
        std::cerr << "Error: index out of bounds." << std::endl;
    }
}

linet Grid::getRowValues(int _row){
    if(_row < gridSize*gridSize){
        return values[_row];
    }
    else{
        std::cerr << "Error: index out of bounds." << std::endl;
    }
    return linet();
}

linet Grid::getColValues(int _col){
    if(_col < gridSize*gridSize){
        linet res(gridSize*gridSize);
        for(int i = 0; i < gridSize*gridSize; i++){
            res[i] = values[i][_col];
        }
        return res;
    }
    else{
        std::cerr << "Error: index out of bounds." << std::endl;
    }
    return linet();
}

gridt Grid::getBlockValues(int _row, int _col){
    if(_row < gridSize*gridSize && _col < gridSize*gridSize){
        gridt block(gridSize, linet(gridSize));
        for(int i = 0; i < gridSize; i++){
            for(int j = 0; j < gridSize; j++){
                block[i][j] = values[_row*gridSize + i][_col*gridSize + j];
            }
        }
        return block;
    }
    else{
        std::cerr << "Error: index out of bounds." << std::endl;
    }
    return gridt();
}

bool Grid::isRowFinished(int r){
	linet row = getRowValues(r);
	if(find(row.begin(), row.end(), 0) == row.end()){
		return true;
	}
	else{
		return false;
	}
}

bool Grid::isColFinished(int c){
	linet col = getColValues(c);
	if(find(col.begin(), col.end(), 0) == col.end()){
		return true;
	}
	else{
		return false;
	}
}

bool Grid::isBlockFinished(int _r, int _c){
	gridt block = getBlockValues(_r, _c);
	for(int i = 0; i < gridSize; i++){
            for(int j = 0; j < gridSize; j++){
		if(block[i][j] == 0){
			return false;
		}		
	    }
        }
	return true;
}



linet Grid::operator[](int i){
    if(i < gridSize*gridSize){
        return values[i];
    }
    else{
        std::cerr << "Error: index out of bounds." << std::endl;
    }
    return linet();
}

bool Grid::operator==(const Grid& other){
    bool flag = true;
    if(gridSize != other.gridSize){
        flag = false;
    }
    else{
        for(int i = 0; i < gridSize*gridSize; ++i){
            for(int j = 0; j < gridSize*gridSize; ++j){
                if(values[i][j] != other.values[i][j]){
                    flag = false;
                }
            }
        }
    }
    return flag;
}

void Grid::write(std::string file_out) {
    std::ofstream file(file_out);
    if (file.is_open()) {
        file << gridSize << std::endl;
        for (int i = 0; i < gridSize*gridSize; ++i) {
            for (int j = 0; j < gridSize*gridSize; ++j) {
                file << values[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file." << std::endl;
    }
}

void Grid::printGrid(){
    for(int i = 0; i < gridSize*gridSize; i++){
        if(i % gridSize == 0){
            for(int k = 0; k < 2*(gridSize+1)*gridSize+1; k++){
                std::cout << "-";
            }
            std::cout << std::endl;
        }
        for(int j = 0; j < gridSize*gridSize; j++){
            if(j%gridSize == 0){
                std::cout << "| ";
            }
            std::cout << values[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    for(int k = 0; k < 2*(gridSize+1)*gridSize+1; k++){
        std::cout << "-";
    }
    std::cout << std::endl << std::endl;
}
