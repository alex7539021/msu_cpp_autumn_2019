#include "BinSort.h"

void make_clean(size_t N) {
    for (size_t i = 0; i < N; i++) {
        std::system(("rm " + std::to_string(i)+ ".txt").c_str());
    }
}

void FileSort(const std::string &fName) {

    typedef std::istream_iterator<uint64_t> Iter;

    std::ifstream f;
    f.open(fName);
    if (!f) {
        throw (std::runtime_error(fName));
    }

    auto *buf = new uint64_t[CHUNK];
    std::vector<std::string> set_fs;

    std::ofstream output;

    size_t num = 0;
    for (; f; num += 2) {
        f.read(reinterpret_cast<char *>(buf), CHUNK);
        size_t read_size = f.gcount() / sizeof(uint64_t);

        set_fs.push_back(std::to_string(num) + ".txt");
        set_fs.push_back(std::to_string(num + 1) + ".txt");
        if (read_size > 0) {
            size_t mid = read_size / 2;

            std::thread t1([buf, mid]() {
                    std::sort(buf, buf + mid);
                }
            );
            std::thread t2([buf, mid, read_size]() {
                    std::sort(buf + mid, buf + read_size);
                }
            );
            t1.join();
            t2.join();
            
            output.open(set_fs[num]);
            if (!output) {
                delete[] buf;
                throw (std::runtime_error(set_fs[num]));
            }
            for (size_t i = 0; i < read_size / 2; i++) {
                output << buf[i] << ' ';
            }
            output.close();

            output.open(set_fs[num + 1]);
            if (!output) {
                delete[] buf;
                throw (std::runtime_error(set_fs[num + 1]));
            }
            for (size_t i = mid; i < read_size; i++) {
                output << buf[i] << ' ';
            }
            output.close();
        }
    }
    f.close();
    delete[] buf;

    auto cmp = [](const std::pair<Iter, Iter> &l, 
                            const std::pair<Iter, Iter> &r) {
        return *r.first < *l.first;
    };
    std::priority_queue<std::pair<Iter, Iter>, std::vector<std::pair<Iter, Iter>>, decltype(cmp)> elem_heap(cmp);
    std::fstream f_stream[num];

    for (size_t i = num; i > 0; i--) {
        f_stream[i - 1].open(set_fs[i - 1]);
        elem_heap.emplace(Iter(f_stream[i - 1]), Iter());
    }
    
    output.open(newFileName);
    if (!output) {
        throw (std::runtime_error(newFileName));
    }

    while (!elem_heap.empty()) {
        auto elem = elem_heap.top();
        elem_heap.pop();
        output << *elem.first << ' ';
        *elem.first++;
        if (elem.first == elem.second) {
            continue;
        }
        elem_heap.emplace(elem);
    }
    output.close();

    make_clean(num);
}