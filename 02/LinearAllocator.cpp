#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(std::size_t maxSize): maxSize(maxSize), curSize(0) {
    ptr = new char[maxSize];
}

char *LinearAllocator::alloc(std::size_t size) {
    if (curSize + size > maxSize) {
        return nullptr;
    }
    char* new_ptr = ptr + curSize;
    curSize += size;
    return new_ptr;
}

void LinearAllocator::reset() {
    curSize = 0;
}

LinearAllocator::~LinearAllocator() {
    delete [] ptr;
}
