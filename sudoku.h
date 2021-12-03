#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

class Sudoku {
  public:
    bool read();
    void print();
    void answer();

    // generate
    static void generate();

    // transform
    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    void solve();

  private:
    void update(int, int, int);
    bool pre_fill();
    bool DFS();

    int filled = 0;
    int map[9][9];
    bool note[9][9][9]; //9*9*9
    int num[9][9];
    int solution[9][9];
    int num_solution = 0;
};

#endif // SUDOKU_H
