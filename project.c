#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define max_history_size 15
#define FORTUNE_FILE NULL //address of fortune file
#define MEMINFO_FILE "/proc/meminfo" //address of memory info file
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
	buf = getlogin();
	while(run){
		printf("%s@%c$\n", hostname, *buf);
		scanf("%d", &task);
	switch(task){
		default:
			printf("error");
		case 1:
			//copy file into new directory
			FILE *fp1, *fp2;
			fp1 = fopen(argv[1], "r");
			fp2 = fopen(argv[2], "w");
			if(!fp1 || !fp2){ printf("error"); }
			char c;
			while((c=fgetc(fp1)) != EOF){ fputc(c, fp2); }
			fclose(fp1);
			fclose(fp2);
			insert(1);
			break;
		case 2:
			//show command history
			insert(2);
			if(front == -1){ printf("command history empty\n"); }
			else{ for(int i = front; i <= rear; i++) {
				switch(command_history[i]){
				case 1:
				printf("copy file\n");
				break;
				case 2:
				printf("command history displayed\n");
				break;
				case 3:
				printf("program free used\n");
				break;
				case 4:
				printf("fortune line displayed\n");
				break;
				case 5:
				printf("fork system call used\n");
				break;
				case 6:
				printf("wait system call used\n");
				break;
				case 7:
				printf("execl system call used\n");
				break;
				case 8:
				printf("execlp system call used\n");
				break;
				}
				}
			}
			break;
		case 3:
			//implement free program
			
			insert(3);
			break;
		case 4:
			//implement fortune
			FILE *file;
			char *line = NULL;
			size_t len = 0;
			ssize_t read;
			file = fopen(FORTUNE_FILE, "r");
			if(file == NULL){ printf("error"); }
			srand(time(NULL));
			int line_count = 0;
			while((read = getline(&line, &len, file)) != -1){
			line_count++;
			if(rand()%line_count == 0){
			printf("%s", line);
			}
			}
			fclose(file);
			if(line){ free(line); }
			insert(4);
			break;
		case 5:
			//implement system call fork
			int rd1 = fork();
			if(rd1==0){ printf("I am child process, my pid is %d\n", (int) getpid()); }
			if(rd1>0){ printf("I am parent process, my pid is %d\n", (int) getpid()); }
			insert(5);
			break;
		case 6:
			//implement system call wait
			int rd2 = fork();
			if(rd2 == 0){ printf("I am child process, my pid is %d\n", (int) getpid()); }
			if(rd2 > 0){ 
				printf("I am parent process, my pid is %d\n", (int) getpid());
				wait(NULL);
				printf("Child process has been terminated\n"); }
			insert(6);
			break;
		case 7:
			//implement system call exec
			char *binaryPath = "/bin/ls";
			char *arg1 = "-lh";
			char *arg2 = "/home";
			execl(binaryPath, binaryPath, arg1, arg2, NULL);
			insert(7);
			break;
		case 8:
			//implement system call execlp
			char *programName = "ls";
			char *arg3 = "-lh";
			char *arg4 = "/home";
			execlp(programName, programName, arg3, arg4, NULL);
			insert(8);
			break;
	}
	free(buf);
	return 0;
        }
}
