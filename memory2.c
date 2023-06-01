#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    int num = 0;
    while (1) {
        if(num >= 10){
	    num = 1;
	}
	else{
	    num++;
	}
	printf("Current num value: %d\n", num);

        // Print memory information
        printMemoryInfo();

        // Sleep for a certain duration
        sleep(3);
    }

    return 0;
}
