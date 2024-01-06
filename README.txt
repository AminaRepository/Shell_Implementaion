This is a project done for the Operating Systems course
Group members: Amina Hukic, Eldar Gljiva

files:
project.c
fortune.txt (needed for fortune lines)
add_on.txt (used to test copy file task)

Assignment question answers:

Q1: Do the following actions require OS to use kernel mode or user mode is sufficient? Explain
1. A program wants to read from disk.
In most operating systems, kernel mode is required to read from a disk. When a process needs to access data stored on a disk, it typically issues a system call to the OS's kernel requesting the data. The kernel then handles the request and performs the necessary operations to read the data from the disk.
The reason kernel mode is needed is that disks are typically managed by the OS and the kernel has direct access to the hardware resources.

2. Reading the current time from the hardware clock.
Reading from the hardware clock requires kernel mode privileges in most OS. The hardware clock (or Real-Time Clock RTC) is a hardware component that keeps track of current time even when the PC is powered off. Since it is part of hardware, kernel mode is needed.

Q2: Explain the purpose of a system call. There are different sets of system calls: list them and give at least 2 examples of a system call for each category.
The purpose of a system call is to provide a secure and controlled interface between the user-level processes and the kernel. 
Some common sets of system calls including examples are:
- process control system calls; fork(), exec(), wait()
- file management system calls; open(), read(), write()
- device management system calls; ioctl(), read(), write()
- communication system calls; socket(), bind(), send()
- memory management system calls; malloc(), free(), mmap()

Outline of what was done for the assignement:
At first we went through all the tasks given in the shell project pdf and went on to implement each required functionality one by one. 
After each functionality had basic code, we worked on optimizing and modifying the code, as well as implementing further functionalities tagged as intermediate and advanced.

Challenges encountered along the way were mostly confusion on what to do, how to start, how to implement various parts that we did not learn about and had to figure out ourselves with no help.
There were some issues working with files, struggling to access them.
There was also a repeated issue of the while loop getting ignored and the code ending after only one input. There was nothing showcasing me what causes it and the code functions well in places other than the command line.

Sources used were in large parts stackOverflow, ChatGPT, as well as various sites holding fragments of c code.



pdf file explaining necessary implementations and tasks;

Operating Systems Project

Purpose: The purpose of this project is to familiarize you with the mechanics of process control
through the implementation of a shell user interface. This includes the relationship between
child and parent processes, the steps needed to create a new process, shell variables, and an
introduction to user-input parsing and verification.

Task 1.1: The shell (command line) is just a program that continually asks for user input,
perhaps does something on the user’s behalf, resets itself, and again asks for user input. Design
and implement a basic shell interface that supports the execution of other programs and a
series of built-in functions. The shell should be robust (e.g., it should not crash under any
circumstance beyond machine failure).

Basic: The prompt should look like this:
prompt$
Advanced: The prompt should look like this:
machinename@username:~$
Where machinename and username should change depending on the machine and user. //implemented

Task 1.2: Shell programs/commands.

Basic: Implement the basic functionality of the following programs: cp, history, free, fortune. //implemented
Intermediate: Provide a few options and/or arguments for at least two programs. Additional
points for creativity (e.g. implementing something that does not exist in bash, or differently than
it is done in bash).
Advanced: Allow piping or at least redirecting output to a text file.

Task 1.3: System calls.

Basic: Within the C-programming example of your choice, implement the following system calls: fork(), wait(), and exec(). //implemented
Intermediate: Within the C-programming example of your choice, implement rfork(), execlp(). //implemented
Additionally: Carefully explore and then implement the forkbomb.

Task 1.4: Add some colors to your shell and name. //implemented

