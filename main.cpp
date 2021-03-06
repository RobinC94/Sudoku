#include <iostream>
#include "sudoku.h"

std::vector<std::vector<char> > buildSudoku(){
    std::vector<std::vector<char> > res(9);
    // res[0] = {'0','0','8','0','0','0','2','0','0'};
    // res[1] = {'0','3','0','8','0','2','0','6','0'};
    // res[2] = {'7','0','0','0','9','0','0','0','5'};
    // res[3] = {'0','5','0','0','0','0','0','1','0'};
    // res[4] = {'0','0','4','0','0','0','6','0','0'};
    // res[5] = {'0','2','0','0','0','0','0','7','0'};
    // res[6] = {'4','0','0','0','8','0','0','0','6'};
    // res[7] = {'0','7','0','1','0','3','0','9','0'};
    // res[8] = {'0','0','1','0','0','0','8','0','0'};
    
    // res[0] = {'0','0','0','0','0','0','0','0','0'};
    // res[1] = {'0','0','0','0','0','0','0','0','0'};
    // res[2] = {'0','0','0','0','0','0','0','0','0'};
    // res[3] = {'0','0','0','0','0','0','0','0','0'};
    // res[4] = {'0','0','0','0','0','0','0','0','0'};
    // res[5] = {'0','0','0','0','0','0','0','0','0'};
    // res[6] = {'0','0','0','0','0','0','0','0','0'};
    // res[7] = {'0','0','0','0','0','0','0','0','0'};
    // res[8] = {'0','0','0','0','0','0','0','0','0'};
    res[0] = {'0','0','9','7','4','8','0','0','0'};
    res[1] = {'7','0','0','0','0','0','0','0','0'};
    res[2] = {'0','2','0','1','0','9','0','0','0'};
    res[3] = {'0','0','7','0','0','0','2','4','0'};
    res[4] = {'0','6','4','0','1','0','5','9','0'};
    res[5] = {'0','9','8','0','0','0','3','0','0'};
    res[6] = {'0','0','0','8','0','3','0','2','0'};
    res[7] = {'0','0','0','0','0','0','0','0','6'};
    res[8] = {'0','0','0','2','7','5','9','0','0'};
    return res;
}

int main() {
    Sudoku sudoku;
    sudoku.init(buildSudoku());
    sudoku.display();
    sudoku.solve();
    sudoku.display();
    return 0;
}