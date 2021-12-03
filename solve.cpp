#include "sudoku.h"
#include <iostream>
#include <ctime>
using namespace std;

int main() {
    cin.tie(0);
    Sudoku susu;
    susu.read();
    susu.solve();
    susu.answer();
    return 0;
}
