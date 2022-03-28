#ifndef __Allocator__
	
	#include <iostream>
	
	class Allocator {
		char* myMemory = nullptr;
		size_t offset = 0;
		size_t myMemorySize = 0;
	public:
		void makeAllocator(size_t maxSize) {
			if (maxSize <= 0)
				return;
			if (myMemory != nullptr)
				delete[] myMemory;
			myMemorySize = maxSize;
			myMemory = new char[maxSize];
			offset = 0;
		}
		char* alloc(size_t size) {
			if (myMemorySize - offset < size || size <= 0)
				return nullptr;
			offset += size;
			return myMemory + offset - size;
		}
		void reset() {
			offset = 0;
		}
		~Allocator() {
			if (myMemorySize != 0)
				delete[] myMemory;
		}
	};

#endif