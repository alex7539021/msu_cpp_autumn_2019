#include "LinearAllocator.h"
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

void test(int num) {
    switch (num) {
    case 0: 
        {
            LinearAllocator p(4);

            char *p1 = p.alloc(2);
            assert(p1 != nullptr);

            p1 = p.alloc(3);
            assert(p1 == nullptr);

            p.reset();

            p1 = p.alloc(3);
            assert(p1 != nullptr);

            cout << "test 1: OK" << endl;
            return;
        }

    case 1: 
        {
            LinearAllocator p(10);

            char *p1 = p.alloc(3);
            char *p2 = p.alloc(2);
            assert(p1 != p2);

            p.reset();

            p2 = p.alloc(3);
            assert(p1 == p2);

            cout << "test 2: OK" << endl;
            return;
        }

    case 2:
        {
            LinearAllocator p(10);

            char *p1 = p.alloc(4);
            for (int i = 0; i < 4; ++i) {
                p1[i] = '1';
            }

            char *p2 = p.alloc(2);
            for (int i = 0; i < 2; ++i) {
                p2[i] = '2';
            }

            char *p3 = p.alloc(2);
            for (int i = 0; i < 2; ++i) {
                p3[i] = '3';
            }

            assert(!strcmp(p1, "11112233"));

            cout << "test 3: OK" << endl;
        }

    default:
        return;
    }
}

void interface (int max, LinearAllocator &p) {
    int sum = 0;
    while (1) {
        char c;
        cin >> c;

        switch (c) {
        case 'E': 
            return;

        case 'R':
            p.reset();
            sum = 0;
            cout << "Free " << max << " out of " << max << endl;
            break;

        case 'N':
            int n;
            cin >> n;
            if (p.alloc(n) != nullptr) {
                sum += n;
                cout << "Free " << max - sum << " out of " << max << endl;
            } else {
                cout << "Not enough storage!" << endl;
            }
            break;

        default:
            return;
        }
    }
}

int main (int argc, char const *argv[]) {

    if (!strcmp(argv[1], "TEST")) {
        for (int i = 0; i < 3; ++i) {
            test(i);
        }
        return 0;
    }

    if (!strcmp(argv[1], "RUN")) {
        int max;
        cout << "Enter the MAX size of the allocator:" << endl;
        cin >> max;
        LinearAllocator p(max);
        cout << "Enter \"N [number]\" to alloc (for ex. \"N 12\")\n  or \"R\" to reset\n  or \"E\" to exit" << endl;

        interface(max, p);

        return 0;
    }
}
