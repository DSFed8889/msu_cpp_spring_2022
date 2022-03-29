#ifndef __Allocator__
namespace allocator {
	class Allocator {
   		char* myMemory = nullptr;
    	size_t offset = 0;
    	size_t myMemorySize = 0;
	public:
		void makeAllocator(size_t maxSize);
		char* alloc(size_t size);
		void reset();
		~Allocator();
	};
}

#endif