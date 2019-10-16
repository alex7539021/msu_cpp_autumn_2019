#include <iostream>
#include <cstring>

using namespace std;

void error() {
    cout << "error";
    exit(1);
}

char get_char(char const *argv, unsigned int &i) {

    if (i == strlen(argv)) {
        return '\n';
    }

    char c;
    while ((c = argv[i++]) == ' ');
    return c;
}

int get_num(char const *argv, unsigned int &i) {

    char c;
    int result = 0, sign = 1;

    c = get_char(argv, i);

    if (c == '-') {
        sign = -1;
        c = get_char(argv, i);
    }

    if ((c < '0') || (c > '9')) {
        error();
    }

    while ((c >= '0') && (c <= '9')) {
        result = result * 10 + c - '0';
        c = get_char(argv, i);
    }

    if (c != '\n') {
        i--;
    }

    return result * sign;
}

int make_summand(char const *argv, unsigned int &i) {

    int result = get_num(argv, i);
    char c;

    while (1) {

        c = get_char(argv, i);

        if ((c == '-') || (c == '+')) {
            i--;
            break;
        }

        if (c == '\n') {
            break;
        }

        if ((c != '*') && (c != '/')) {
            error();
        }

        if (c == '*') {
            result *= get_num(argv, i);
        } else {
            int k = get_num(argv, i);
            if (k == 0) {
                error();
            }
            result /= k;
        }
    }

    return result;
}

int main(int argc, char const *argv[]) {
    
    if (argc != 2) {
        error();
    }

    unsigned int i = 0;

    int result = make_summand(argv[1], i);
    char c;

    while (1) {

        c = get_char(argv[1], i);

        if (c == '\n') {
            break;
        }

        if ((c != '+') && (c != '-')) {
            error();
        }

        if (c == '+') {
            result += make_summand(argv[1], i);
        } else {
            result -= make_summand(argv[1], i);
        }
    }

    cout << result;

    return 0;
}