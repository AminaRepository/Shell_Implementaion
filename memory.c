#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    size_t page_size = getpagesize();
    size_t memory_size = 4096; // Allocate 4KB of memory
    size_t aligned_size = (memory_size / page_size + 1) * page_size;

    // Allocate memory using mmap
    void* memory = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Memory allocated at address: %p\n", memory);

    // Access the allocated memory
    int* data = (int*)memory;
    *data = 42;
    printf("Value stored in memory: %d\n", *data);

    // Deallocate memory using munmap
    int result = munmap(memory, aligned_size);
    if (result != 0) {
        perror("munmap");
        exit(1);
    }

    printf("Memory deallocated\n");

    return 0;
}
