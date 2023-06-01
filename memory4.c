#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

void printMemoryInfo() {
    char status_path[256];
    sprintf(status_path, "/proc/%d/status", getpid());

    FILE* status_file = fopen(status_path, "r");
    if (status_file == NULL) {
        perror("fopen");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), status_file)) {
        if (strncmp(line, "VmSize:", 7) == 0 || strncmp(line, "VmRSS:", 6) == 0) {
            printf("%s", line);
        }
    }

    fclose(status_file);
}

int main() {
    // Map an empty page
    size_t page_size = getpagesize();
    void* memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Memory mapped at address: %p\n", memory);

    // Write data into the memory-mapped page
    const char* message = "Hello, Memory Mapping!";
    size_t message_len = strlen(message) + 1;
    memcpy(memory, message, message_len);

    while (1) {
        // Your program logic goes here
        // ...

        // Print memory information
        printMemoryInfo();

        // Sleep for a certain duration
        sleep(5);
    }

    // Unmap the memory
    int result = munmap(memory, page_size);
    if (result != 0) {
        perror("munmap");
        exit(1);
    }

    printf("Memory unmapped\n");

    return 0;
}
