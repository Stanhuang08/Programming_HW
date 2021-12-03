#include "sudoku.h"
#include <iostream>
using namespace std;

int main() {
    cin.tie(0);
    Sudoku susu;
    int type, x, y;
    if (susu.read()) {
        do {
            cin >> type;
            if (type == 1) {
                cin >> x >> y;
                susu.swapNum(x, y);
            } else if (type == 2) {
                cin >> x >> y;
                susu.swapRow(x, y);
            } else if (type == 3) {
                cin >> x >> y;
                susu.swapCol(x, y);
            } else if (type == 4) {
                cin >> x;
                susu.rotate(x);
            } else if (type == 5) {
                cin >> x;
                susu.flip(x);
            }
        } while (type);
        susu.print();
        return 0;
    }
}
