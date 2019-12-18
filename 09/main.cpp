#include "BinSort.h"

using namespace std;

int main() {

    ofstream file(FileName);
    if (!file) {
        cerr << "Can't open file" << endl;
        return 1;
    }
    for (size_t i = 0; i < 20; i++) {
        uint64_t num = std::rand() % 100;
        file.write((char *) &num, sizeof(uint64_t));
    }
    file.close();

    try {
        FileSort(FileName);
    } catch (const std::runtime_error &err) {
        cerr << "Can't open file" << endl;
        return 1;
    }

    return 0;
}