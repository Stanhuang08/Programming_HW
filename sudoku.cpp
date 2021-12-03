#include "sudoku.h"
#include <iostream>
#include <ctime>
using namespace std;

//read
bool Sudoku::read() {
    //read, check unvalid num, get filled counts
    int row, col, i;
    filled = 0;
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (!(cin >> map[row][col])) return false;
            if (map[row][col] != 0) { //filled
                ++filled;
                num[row][col] = -1;
                for (i = 0; i < 9; i++) note[row][col][i] = false;
            } else { //unfilled
                num[row][col] = 9;
                for (i = 0; i < 9; ++i) note[row][col][i] = true;
            }
        }
    }
    return true;
}

//print_answer
void Sudoku::print() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            cout << map[row][col];
            if (col == 8) cout << "\n";
            else cout << " ";
        }
    }
}

void Sudoku::answer() {
    if (num_solution == 1) {
        cout << 1 << endl;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                cout << solution[row][col];
                if (col == 8) cout << "\n";
                else cout << " ";
            }
        }
    } else if (num_solution == 0) cout << 0 << endl;
    else cout << 2 << endl;
}

//generate
void Sudoku::generate() {
    int gen[81]  = {1, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 7, 0, 0, 5,
                    0, 8, 0, 9, 0, 3, 4, 2, 0,
                    0, 0, 2, 0, 4, 0, 8, 0, 0,
                    8, 1, 0, 0, 2, 0, 0, 0, 0,
                    0, 0, 7, 0, 0, 0, 0, 5, 6,
                    6, 5, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 3, 0, 0, 0, 0, 9, 0,
                    0, 0, 0, 0, 0, 0, 7, 0, 4
                   };
    for (int i = 0; i < 81; ++i) {
        cout << gen[i];
        if (i % 9 != 8) cout << " ";
        else cout << endl;
    }
}

// transform
void Sudoku::swapNum(int x, int y) {
    if (x < 1 || x > 9 || y < 1 || y > 9) return;
    int row, column;
    for (row = 0; row < 9; row++) {
        for (column = 0; column < 9; column++) {
            if (map[row][column] == x) map[row][column] = y;
            else if (map[row][column] == y) map[row][column] = x;
        }
    }
}

void Sudoku::swapRow(int x, int y) {
    if (x != 0 && x != 1 && x != 2) return;
    if (y != 0 && y != 1 && y != 2) return;
    if (x == y) return;
    int temp[3][9];
    int row, column;
    for (row = 0; row < 3; ++row) {
        for (column = 0; column < 9; ++column) {
            temp[row][column] = map[(row + 3*x)][column];
            map[(row + 3*x)][column] = map[(row + 3*y)][column];
            map[(row + 3*y)][column] = temp[row][column];
        }
    }
}

void Sudoku::swapCol(int x, int y) {
    if (x != 0 && x != 1 && x != 2) return;
    if (y != 0 && y != 1 && y != 2) return;
    if (x == y) return;
    int temp[9][3];
    int row, col;
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 3; ++col) {
            temp[row][col] = map[row][(col + 3*x)];
            map[row][(col + 3*x)] = map[row][(col + 3*y)];
            map[row][(col + 3*y)] = temp[row][col];
        }
    }
}

void Sudoku::rotate(int x) {
    if ( x > 0) x = (x % 4);
    int temp[9][9];
    int i, row, col;


    for (i = 0; i < x; ++i) {
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++ col) {
                temp[row][(8 - col)] = map[col][row];
            }
        }
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++col) {
                map[row][col] = temp[row][col];
            }
        }
    }
}

void Sudoku::flip(int x) {
    if (x != 0 && x != 1) return;
    int row, col, temp[9][9];
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (x == 0) temp[(8 - row)][col] = map[row][col]; //up-down
            else temp[row][(8 - col)] = map[row][col]; //left-right
        }
    }
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            map[row][col] = temp[row][col];
        }
    }
}

//solve
void Sudoku::update(int row, int col, int n) {
    int i, j;
    //update_row
    for (i = 0; i < 9; ++i) {
        if ((note[row][i][(n-1)]) == true) {
            note[row][i][(n-1)] = false;
            --num[row][i];
        }
    }
    //update_col
    for (i = 0; i < 9; ++i) {
        if (note[i][col][(n-1)] == true) {
            note[i][col][(n-1)] = false;
            --num[i][col];
        }
    }
    //update_block (index shift to [0, 0] in each block)
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (note[((row/3)*3 + i)][((col/3)*3 + j)][(n-1)] == true) {
                note[((row/3)*3 + i)][((col/3)*3 + j)][(n-1)] = false;
                --num[((row/3)*3 + i)][(col/3)*3 + j];
            }
        }
    }
}

bool Sudoku::pre_fill() {
    bool flag;
    int row, col, i, check[9];
    //type 1 (fill one)
    do {
        flag = false;
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++ col) {
                if (num[row][col] == 0) return false; //trash game bye==
                else if (num[row][col] == 1) { //fill it!
                    for (i = 0; i < 9; ++i) {
                        while (note[row][col][i]) {
                            map[row][col] = i + 1;
                            ++filled;
                            note[row][col][i] = false;
                            num[row][col] = -1;
                            update(row, col, i + 1);
                            flag = true;
                        }//after each filling, update note[], num[]
                    }
                }
            }
        }
        //type 2 (check row)
        for (row = 0; row < 9; ++row) {
            for (i = 0; i < 9; ++i) check[i] = 0;
            for (col = 0; col < 9; ++col) {
                for (i = 0; i < 9; ++i) {
                    if (note[row][col][i] == true) check[i] += 1;
                    else check[i] = check[i];
                }
            }
            for (col = 0; col < 9; ++col) {
                if (map[row][col] != 0) check[map[row][col] - 1] = -1;
            }
            for (i = 0; i < 9; ++i) {
                if (check[i] == 0) return false;
                else if (check[i] == 1) { //number i can be filled
                    for (col = 0; col < 9; ++col) { //where to fill?
                        if (note[row][col][i] == true) { //here.
                            map[row][col] = i + 1;
                            ++filled;
                            num[row][col] = -1;
                            for (int j = 0; j < 9; ++j) note[row][col][j] = false;
                            update(row, col, i+1);
                            flag = true;
                        }
                    }
                }
            }
        }
        //type 3 (check col)
        for (col = 0; col < 9; ++col) {
            for (i = 0; i < 9; ++i) check[i] = 0;
            for (row = 0; row < 9; ++row) {
                for (i = 0; i < 9; ++i) check[i] += (note[row][col][i] == true ? 1:0);
            }
            for (row = 0; row < 9; ++row) {
                if (map[row][col] != 0) check[map[row][col] - 1] = -1;
            }
            for (i = 0; i < 9; ++i) {
                if (check[i] == 0) return false;
                else if (check[i] == 1) {
                    for (row = 0; row < 0; ++row) {
                        if (note[row][col][i] == true) {
                            map[row][col] = i + 1;
                            ++filled;
                            num[row][col] = -1;
                            for (int j = 0; j < 9; ++j) note[row][col][j] = false;
                            update(row, col, i+1);
                            flag = true;
                        }
                    }
                }
            }
        }
    } while (flag);
    return true;
}

bool Sudoku::DFS() {
    if (pre_fill() == false) return true;
    int row, col;
    if (filled >= 81) {
        ++num_solution;
        if (num_solution == 1) {
            for (row = 0; row < 9; ++row) {
                for (col = 0; col < 9; ++col) solution[row][col] = map[row][col];
            }
            return true;
        } else return false;
    }
    int i, j, r, c, map_r[9][9], note_r[9][9][9], num_r[9][9], fiiled_r = filled, flag = false;
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            map_r[row][col] = map[row][col];
            num_r[row][col] = num[row][col];
            for (i = 0; i < 9; ++i) note_r[row][col][i] = note[row][col][i];
        }
    }
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (map[row][col] == 0) {
                r = row;
                c = col;
                flag = true;
                break;
            }
        }
        if (flag) break;
    }
    for (i = 0; i < 9; ++i) {
        if (note[r][c][i] == true) {
            map[r][c] = i + 1;
            ++filled;
            for (j = 0; j < 9; ++j) note[r][c][j] = false;
            num[r][c] = -1;
            update(r, c, i+1);

            if (DFS() == true) { //wrong try(pre_fill = false)
                filled = fiiled_r;
                for (row = 0; row < 9; ++row) {
                    for (col = 0; col < 9; ++col) {
                        map[row][col] = map_r[row][col];
                        num[row][col] = num_r[row][col];
                        for (j = 0; j < 9; ++j) note[row][col][j] = note_r[row][col][j];
                    }
                }
            } else return false;
        }
    }
    return true;
}

void Sudoku::solve() {
    int row, col;
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (map[row][col]) update(row, col, map[row][col]);
        }
    }
    if (pre_fill() == false) num_solution = 0;
    else if (filled < 17) num_solution = 2;
    else DFS();
}
