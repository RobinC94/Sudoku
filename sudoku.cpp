#include "sudoku.h"

Sudoku::Sudoku(){
    clear();
}

void Sudoku::clear(){
    for (int i = 0; i < 81; ++i){
        board[i] = 0;
        record[i].set();
    }
    filled = 0;
    valid = true;
}

bool Sudoku::singleSolution(){
    uint8_t oldBoard[81];
    std::bitset<9> oldRecord[81];
    int oldFilled = filled;
    int minChoice = 9;
    int minPos = -1;
    for (int i = 0; i < 81; ++i){
        oldBoard[i] = board[i];
        oldRecord[i] = record[i];
    }
    bool res = solve();
    for (int i = 0; i < 81; ++i){
        board[i] = oldBoard[i];
        record[i] = oldRecord[i];
    }
    return res;
}

bool Sudoku::fillValidBlank(){
    bool action = false;
    for (int i = 0; i < 9; ++i){
        for (uint8_t var = 0; var < 9; ++var){
            int posH = -1, posW = -1, posS = -1;
            for (int j = 0; j < 9; ++j){
                auto curRec = record[i*9+j];
                if(curRec.count() == 1 && curRec[var] == 1){
                    std::cout << 0 << i+1 << j+1 << (int)var+1 << std::endl;
                    action = setValue(i, j, var+1);
                }
            }
            for (int j = 0; j < 9; ++j){
                auto curRecH = record[i*9+j];
                if (curRecH[var] == 1){
                    if (posH == -1){
                        posH = j;
                    }
                    else{
                        posH = 10;
                    }
                }
            }
            if (posH >=0 && posH < 9){ 
                std::cout << 1 << i+1 << posH+1 << (int)var+1 << std::endl;
                action = setValue(i, posH, var+1);
            }
            for (int j = 0; j < 9; ++j){
                auto curRecW = record[j*9+i]; 
                if (curRecW[var] == 1){
                    if (posW == -1){
                        posW = j;
                    }
                    else{
                        posW = 10;
                    }
                }
            }
            if (posW >=0 && posW < 9){ 
                std::cout << 2 << posW+1 << i+1 << (int)var+1 << std::endl;
                action = setValue(posW, i, var+1);
            }
            for (int j = 0; j < 9; ++j){
                auto curRecS = record[(i/3*3+j/3)*9+(i%3*3+j%3)];  
                if (curRecS[var] == 1){
                    if (posS == -1){
                        posS = j;
                    }
                    else{
                        posS = 10;
                    }
                }
            }
            if (posS >=0 && posS < 9){ 
                std::cout << 3 << i/3*3+posS/3+1 << i%3*3+posS%3+1 << (int)var+1 << std::endl;
                action = setValue(i/3*3+posS/3, i%3*3+posS%3, var+1);
            }
            if (!valid){
                return false;
            }
        }
    }
    return action;
}

bool Sudoku::init(std::vector<std::vector<char> > inBoard){
    if (inBoard.size() < 9 || inBoard[0].size() < 9){
        std::cout <<" Invalid board shape!" << std::endl;
        return false;
    }
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (inBoard[i][j] >= '1' && inBoard[i][j] <= '9'){
                bool res = setValue(i, j, inBoard[i][j] - '1' + 1);
                if (!res){
                    clear();
                    std::cout <<" Invalid Sudoku!" << std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}

bool Sudoku::setValue(int h, int w, uint8_t var){
    if (h < 0 || h > 8 || w < 0 || w > 8){
        std::cout << "Invalid index!" << std::endl;
        return false;
    }
    if (record[h*9+w][var-1] == 0) {
        std::cout << "Invalid insert value!" << std::endl;
        valid = false;
        return false;
    }
    board[h*9+w] = var;
    record[h*9+w].reset();
    for (int i = 0; i < 9; ++i){
        record[h*9+i][var-1] = 0;
        record[i*9+w][var-1] = 0;
        int j = i / 3;
        int k = i % 3;
        record[(h/3*3+j)*9+w/3*3+k][var-1] = 0;
    }
    filled++;

    return true;
}

bool Sudoku::solve(){
    while(fillValidBlank()){
        if (!valid){
            return false;
        }
    }
    if (filled == 81)
        return true;
    else{
        uint8_t oldBoard[81];
        std::bitset<9> oldRecord[81];
        int oldFilled = filled;
        int minChoice = 9;
        int minPos = -1;
        for (int i = 0; i < 81; ++i){
            oldBoard[i] = board[i];
            oldRecord[i] = record[i];
            if (record[i].count() > 0 && record[i].count() < minChoice){
                minChoice = record[i].count();
                minPos = i;
            }
        }
        //std::cout << minPos << minChoice << std::endl;
        if (minPos == -1){
            return false;
        }
        for (uint8_t var = 0; var < 9; var++){
            if(record[minPos][var] == 1){
                setValue(minPos/9, minPos%9, var+1);
                if (solve()){
                    return true;
                }
                else
                {
                    for (int i = 0; i < 81; ++i){
                        board[i] = oldBoard[i];
                        record[i] = oldRecord[i];
                        filled = oldFilled;
                    }
                    record[minPos][var] = 0;
                    valid = true;
                    return solve();
                }  
            }
        }
        return false;
    }
}

void Sudoku::display(){
    for (int i = 0; i < 9; ++i){
        std::cout << '|';
        for (int j = 0; j < 9; ++j){
            std::cout << (int)board[i*9+j];
            if (j % 3 == 2){
                std::cout << '|';
            }
            else{
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 9; ++i){
        std::cout << '|';
        for (int j = 0; j < 9; ++j){
            std::cout << record[i*9+j];
            if (j % 3 == 2){
                std::cout << '|';
            }
            else{
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << "filled: " << filled << std::endl;
}