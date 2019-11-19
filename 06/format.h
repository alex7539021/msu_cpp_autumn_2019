#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

template <class T>
std::string to_string(T&& arg) {
    std::ostringstream s;
    s << arg;
    return s.str();
}

std::string format(const std::string& s) {
    return s;
}

template<class... ArgsT>
std::string format(const std::string& s, ArgsT&&... args) {
    std::vector<std::string> arg{to_string(std::forward<ArgsT>(args))...};
    std::ostringstream result;

    unsigned int count = 0;
    while (count < s.length()) {
        if (s[count] == '{') {
            count++;
            if (s[count] == '}') {
                throw std::runtime_error("");
            }
            unsigned int num = 0;
            while (s[count] != '}' && count < s.length()) {
                if (s[count] >= '0' && s[count] <= '9') {
                    num = num * 10 + (s[count] - '0');
                } else {
                    throw std::runtime_error("");
                }
                count++;
            }
            if (num >= arg.size() || count == s.length()) {
                throw std::runtime_error("");
            }
            result << arg[num];
        } else if (s[count] == '}') {
            throw std::runtime_error("");
        } else {
            result << s[count];
        }
        count++;
    }
    return result.str();
}
