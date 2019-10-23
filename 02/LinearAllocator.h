#ifndef LinearAllocator_H
#define LinearAllocator_H

#include <cstddef>

class LinearAllocator {

    char *ptr;
    std::size_t maxSize;
    std::size_t curSize;

public:

    LinearAllocator(std::size_t maxSize);

    char *alloc(std::size_t size);

    void reset();

    ~LinearAllocator();
};

#endif