#include <iostream>
#include <time.h>
#include "Grid.h"
#include "CompleteSearch.h"
#include "OptimisedSearch.h"
#include "Generator.h"
#include "Interface.h"
#include "Game.h"

int main(int argc, char* argv[]){
    /*
    tmp.printGrid();
    
    clock_t t1 = clock();
    OptimisedSearch solver1;
    Grid otv1;
    otv1 = solver1.solve(tmp);
    otv1.printGrid(); 
    clock_t t2 = clock();
    std::cout << (double)(t2-t1)/CLOCKS_PER_SEC << std::endl;
    

    
    clock_t t3 = clock();
    CompleteSearch solver2;
    Grid otv2;
    otv2 = solver2.solve(tmp);
    otv2.printGrid();
    clock_t t4 = clock();
    std::cout << (double)(t4-t3)/CLOCKS_PER_SEC << std::endl;
    */

    //class Generator<OptimisedSearch> gen(3);
    //Grid board = gen.genGrid(40);
    //board.printGrid();
    //OptimisedSearch solver3;
    //Grid otv3;
    //otv3 = solver3.solve(board);
    //otv3.printGrid();    
	
    Game sudoku;
    if(argc == 1){
	    sudoku.game();
    }
    if(argc > 1){
	    endwin();
	    if(argc > 2){
		sudoku.refresh(atoi(argv[2]));
	    }
	    else{
	    	sudoku.refresh();
	    }
    }
    return 0;
}
