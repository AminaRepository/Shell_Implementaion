#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <sys/param.h>

#define max_history_size 15
#define FORTUNE_FILE NULL //address of fortune file
#define MEMINFO_FILE NULL //address of memory info file
int command_history[max_history_size];
int rear = -1;
int front = -1;
 
void enqueue(){ front +=1; }

void insert(int item){
	if(rear == max_history_size-1){ 
		enqueue();
	}
	else{
		rear += 1;
		command_history[rear] = item;
	}
}

int main(int argc, char* argv[]){
	int task;
	bool run = true;
	char hostname[HOST_NAME_MAX + 1];
	gethostname(hostname, HOST_NAME_MAX +1);
	char *buf;
	buf = (char *)malloc(10*sizeof(char));
	if(!buf){ printf("bad buffer"); }
	buf = getlogin();
	while(run){
		printf("\033[0;35m"); //text color set o purple
		printf("%s@%c$\n", hostname, *buf);
		printf("\033[0;34m"); //text color set to blue
		scanf("%d", &task);
		printf("\033[0m"); //text color set to black
	switch(task){
		default:
			printf("error");
		case 1:
			run = false;
			break;

		case 2:
			//copy file into new directory
			FILE *fp1, *fp2;
			char ch, fnamesrc[50], fnamedest[50];
			printf("Source file name: \n");
			scanf("%s", fnamesrc);
			printf("Destination file name: \n");
			scanf("%s", fnamedest);
			fp1 = fopen(fnamesrc, "r");
			fp2 = fopen(fnamedest, "w");
			if(!fp1 || !fp2){ printf("error"); }
			while((ch=fgetc(fp1)) != EOF){ fputc(ch, fp2); }
			fclose(fp1);
			fclose(fp2);
			insert(2);
			break;
		case 3:
			//show command history
			insert(3);
			if(front == -1){ printf("command history empty\n"); }
			else{ for(int i = front; i <= rear; i++) {
				switch(command_history[i]){
				case 2:
				printf("copy file\n");
				break;
				case 3:
				printf("command history displayed\n");
				break;
				case 4:
				printf("program free used\n");
				break;
				case 5:
				printf("fortune line displayed\n");
				break;
				case 6:
				printf("fork system call used\n");
				break;
				case 7:
				printf("wait system call used\n");
				break;
				case 8:
				printf("execl system call used\n");
				break;
				case 9:
				printf("execlp system call used\n");
				break;
				case 10:
				printf("vfork system call used\n");
				break;
				}
				}
			}
			break;
		case 4:
			//implement free program
			FILE *file_free;
    			char line[256];
    			unsigned long long mem_total, mem_free, mem_used, mem_buffers, mem_cached;
			file_free = fopen(MEMINFO_FILE, "r");
    			if (file_free == NULL){ printf("error\n"); }
			while (fgets(line, sizeof(line), file_free)) {
        		if (sscanf(line, "MemTotal: %llu kB", &mem_total) == 1) {
            		continue;
        		} else if (sscanf(line, "MemFree: %llu kB", &mem_free) == 1) {
            		continue;
        		} else if (sscanf(line, "Buffers: %llu kB", &mem_buffers) == 1) {
            		continue;
        		} else if (sscanf(line, "Cached: %llu kB", &mem_cached) == 1) {
            		continue;
        		}
    			}
			mem_used = mem_total - mem_free - mem_buffers - mem_cached;
			printf("             total       used       free     shared    buffers     cache\n");
    			printf("Mem:       %8llu %8llu %8llu          0 %8llu %8llu\n", mem_total, mem_used, mem_free, mem_buffers, mem_cached);
    			printf("-/+ buffers/cache: %8llu %8llu\n", mem_used - mem_buffers - mem_cached, mem_free + mem_buffers + mem_cached);
			fclose(file_free);
			insert(3);
			break;
		case 5:
			//implement fortune
			FILE *file_fortune;
			char *line_fortune = NULL;
			size_t len = 0;
			ssize_t read;
			file_fortune = fopen(FORTUNE_FILE, "r");
			if(file_fortune == NULL){ printf("error"); }
			srand(time(NULL));
			int line_count = 0;
			while((read = getline(&line_fortune, &len, file_fortune)) != -1){
			line_count++;
			if(rand()%line_count == 0){
			printf("%s", line_fortune);
			}
			}
			fclose(file_fortune);
			free(line_fortune);
			insert(4);
			break;
		case 6:
			//implement system call fork
			int rd1 = fork();
			if(rd1==0){ printf("I am child process, my pid is %d\n", (int) getpid()); }
			if(rd1>0){ printf("I am parent process, my pid is %d\n", (int) getpid()); }
			insert(5);
			break;
		case 7:
			//implement system call wait
			int rd2 = fork();
			if(rd2 == 0){ printf("I am child process, my pid is %d\n", (int) getpid()); }
			if(rd2 > 0){ 
				printf("I am parent process, my pid is %d\n", (int) getpid());
				wait(NULL);
				printf("Child process has been terminated\n"); }
			insert(6);
			break;
		case 8:
			//implement system call exec
			char *binaryPath = "/bin/ls";
			char *arg1 = "-lh";
			char *arg2 = "/home";
			execl(binaryPath, binaryPath, arg1, arg2, NULL);
			insert(7);
			break;
		case 9:
			//implement system call execlp
			char *programName = "ls";
			char *arg3 = "-lh";
			char *arg4 = "/home";
			execlp(programName, programName, arg3, arg4, NULL);
			insert(8);
			break;
		case 10:
			//implement system call vfork
			int rd3 = vfork();
			if(rd3 == 0){ printf("I am child process, my pid is %d\n", (int) getpid()); }
			if(rd3 > 0){ printf("I am parent process, my pid is %d\n", (int) getpid()); 
			wait(NULL);
			printf("Child process is terminated\n");
			}
			//my system does not have the necessary rfork library to execute the code, otherwise it should be correct
	}
	return 0;
        }
}
