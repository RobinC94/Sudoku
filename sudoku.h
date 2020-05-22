#include <iostream>
#include <stdint.h>
#include <bitset>
#include <vector>


class Sudoku{
private:
    uint8_t board[81];
    std::bitset<9> record[81];
    int filled;
    bool valid;

    void clear();
    bool singleSolution();
    bool fillValidBlank();

public:
    Sudoku();
    
    bool init(std::vector<std::vector<char> >);
    bool setValue(int h, int w, uint8_t var);
    void randomInit();
    bool solve();
    void display();
};