#include "Matrix.h"

#include <cassert>
#include <iostream>

using namespace std;

void test(int i) {

    switch (i) {
    case 1: {
            const size_t rows = 5;
            const size_t cols = 7;

            Matrix m(rows, cols);

            assert(m.getRows() == 5);
            assert(m.getColumns() == 7);

            m[2][4] = 5; 
            assert(m[2][4] == 5);

            double x = m[4][1];
            assert(x == m[4][1]);

            cout << "test1: OK" << endl;
            break;
        }

    case 2: {
            const size_t rows = 6;
            const size_t cols = 3;

            Matrix m1(rows, cols);
            Matrix m2(rows, cols);
            Matrix m3(rows, cols);
            Matrix m4(rows + 1, cols);

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    m1[i][j] = m2[i][j] = m4[i][j] = i + j;
                    m3[i][j] = i - j;
                }
            }

            assert(m1 == m2);
            assert(m1 != m3);
            assert(m1 != m4);

            cout << "test2: OK" << endl;
            break;
        }

    case 3: {
            const size_t rows = 8;
            const size_t cols = 6;

            Matrix m1(rows, cols);
            Matrix m2(rows, cols);

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    m1[i][j] = 2;
                    m2[i][j] = 12;
                }
            }

            m1 *= 6;

            assert(m1 == m2);

            cout << "test3: OK" << endl;
            break;
        }
    }

    return;
}


int main() {
    for (int i = 0; i < 3; ++i) {
        test(i + 1);
    }
    return 0;
}