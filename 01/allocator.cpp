#include <iostream>
#include "allocator.hpp"

namespace allocator {
    void Allocator::makeAllocator(size_t maxSize) {
        if (maxSize <= 0)
            return;
        if (myMemory != nullptr)
            delete[] myMemory;
        myMemorySize = maxSize;
        myMemory = new char[maxSize];
        offset = 0;
    }

    char* Allocator::alloc(size_t size) {
        if (myMemorySize - offset < size || size <= 0)
            return nullptr;
        offset += size;
        return myMemory + offset - size;
    }

    void Allocator::reset() {
        offset = 0;
    }

    Allocator::~Allocator() {
        if (myMemorySize != 0)
            delete[] myMemory;
    }
}