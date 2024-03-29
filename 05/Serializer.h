#pragma once

#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer {

    static constexpr char Separator = ' ';
    std::ostream &out_;

public:
    explicit Serializer(std::ostream& out)
        : out_(out) {
    }

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template<class... Args>
    Error operator()(Args &&...args) {
        return process(std::forward<Args>(args)...);
    }
    
private:
    template<class T, class... Args>
    Error process(T &&value, Args &&...args) {
        if (write(value) == Error::NoError)
            return process(std::forward<Args>(args)...);
        return Error::CorruptedArchive;
    }

    Error write(uint64_t value) {
        out_ << value << Separator;
        return Error::NoError;
    }

    Error write(bool value) {
        std::string strVal = value ? "true" : "false";
        out_ << strVal << Separator;
        return Error::NoError;
    }

    template<class T>
    Error write(T& value) {
        return Error::CorruptedArchive;
    }

    Error write() {
        return Error::NoError;
    }

    Error process() {
        return Error::NoError;
    }
};

class Deserializer {

    std::istream& in_;

public:
    explicit Deserializer(std::istream& in): in_(in) {}

    template<class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template<class... Args>
    Error operator()(Args &&...args) {
        return process(std::forward<Args>(args)...);
    }

private:

    template<class T, class... Args>
    Error process(T &&value, Args &&...args) {
        if (read(value) == Error::NoError) {
            return process(std::forward<Args>(args)...);
        }
        return Error::CorruptedArchive;
    }

    Error process() {
        return Error::NoError;
    }

    Error read(bool& value) {
        std::string text;
        in_ >> text;
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error read(uint64_t& value) {
        bool err = false;
        std::string str;
        in_ >> str;
        if (str[0] == '-') {
            return Error::CorruptedArchive;
        }
        try {
            value = std::stoull(str);
        } catch(std::exception&) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class T>
    Error read(T& value) {
        return Error::CorruptedArchive;
    }

    Error read() {
        return Error::CorruptedArchive;
    }
};
