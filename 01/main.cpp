#include <iostream>
#include <cstring>
#include <string>

using namespace std;

char get_char(string &argv, unsigned int &i) {

    if (i == argv.size()) {
        return '\n';
    }

    char c;
    while ((c = argv[i++]) == ' ');
    return c;
}

int get_num(string &argv, unsigned int &i, char &error) {

    char c;
    int result = 0, sign = 1;

    c = get_char(argv, i);

    if (c == '-') {
        sign = -1;
        c = get_char(argv, i);
    }

    if ((c < '0') || (c > '9')) {
        error = 1;
        return result;
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

int make_summand(string &argv, unsigned int &i, char &error) {

    int result = get_num(argv, i, error);
    char c;

    while (!error) {

        c = get_char(argv, i);

        if ((c == '-') || (c == '+')) {
            i--;
            break;
        }

        if (c == '\n') {
            break;
        }

        if ((c != '*') && (c != '/')) {
            error = 1;
            return result;
        }

        if (c == '*') {
            result *= get_num(argv, i, error);
        } else {
            int k = get_num(argv, i, error);
            if (k == 0) {
                error = 1;
                return result;
            }
            result /= k;
        }
    }

    return result;
}

int calculator(string &argv, char &error) {

    unsigned int i = 0;

    int result = make_summand(argv, i, error);
    char c;

    while (!error) {

        c = get_char(argv, i);

        if (c == '\n') {
            break;
        }

        if ((c != '+') && (c != '-')) {
            error = 1;
            return result;
        }

        if (c == '+') {
            result += make_summand(argv, i, error);
        } else {
            result -= make_summand(argv, i, error);
        }
    }

    return result;
}

int main(int argc, char const *argv[]) {
    
    if (argc != 2) {
        cout << "error";
        return 1;
    }

    char error = 0;

    string str(argv[1]);

    int result = calculator(str, error);

    if (error) {
        cout << "error";
        return 1;
    }

    cout << result;

    return 0;
}
