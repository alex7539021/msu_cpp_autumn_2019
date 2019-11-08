#include "BigInt.h"

#include <iostream>
#include <cassert>

using namespace std;

void test (int N) {
    switch (N) {
    case 1: {
            cout << "-------------------" << endl;
            BigInt a = 120;
            BigInt b = 320;
            BigInt c = 440;
            cout << a << " + " << b << " = " << (a + b) << endl;
            assert(a + b == c);
            BigInt d = -100;
            BigInt e = 20;
            cout << a << " + " << d << " = " << (a + d) << endl;
            assert(a + d == e);
            BigInt f = -220;
            BigInt h = -320;
            cout << d << " + " << f << " = " << (d + f) << endl;
            assert(d + f == h);
            BigInt g = 0;
            cout << a << " + " << g << " = " << (a + g) << endl;
            assert(a + g == a);

            cout << "test1: OK" << endl;
            break;
        }
    case 2: {
            cout << "-------------------" << endl;
            BigInt a = 320;
            BigInt b = 120;
            BigInt c = 200;
            cout << a << " - " << b << " = " << c << endl;
            assert(a - b == c);
            BigInt d = -200;
            cout << b << " - " << a << " = " << -c << endl;
            assert(b - a == -c);
            cout << "test2: OK" << endl;
            break;
        }
    case 3: {
            cout << "-------------------" << endl;
            BigInt a = 1000;
            BigInt b = 990;
            assert(a != b);
            assert(a > b);
            assert(a >= b);
            assert(a == b == false);
            assert(a <= b == false);
            BigInt c = 1000;
            assert(a == c);
            assert(a >= c);
            assert(a <= c);
            BigInt d = -2000;
            assert(a > d);
            cout << "test3: OK" << endl;
            break;
        }
    case 4: {
            cout << "-------------------" << endl;

            BigInt a(2000000002);
            BigInt b(2000000002);
            
            for (int i = 1; i < 12; ++i) {
                b = b + b;
            }
            for (int i = 1; i < 11; ++i) {
                a = a + a;
            }
            
            cout << a << " + " << a << " = " << b << endl;
            assert(b == a + a);
            cout << "test4: OK" << endl;
            break;
        }
    }
    return;
}

int main () {
    int N = 4;
    for (int i = 0; i < N; ++i) {
        test(i + 1);
    }
    return 0;
}