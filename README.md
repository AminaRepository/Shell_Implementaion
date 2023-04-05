Group members: Amina HUkic, Eldar Gljiva

files: project.c
fortune.txt (needed for fortune lines)
add_on.txt (used to test copy file task)

Assignement question answers:

Q1: Do the following actions require OS to use kernel mode or user mode is sufficient? Explain
1. A program wants to read from disk.
2. Reading the current time from the hardware clock.
Q2: Exolain the purpose of a system call. There are different sets of system calls: list them and give at least 2 examples of a system call for each category.

Outline of what was done for the assignement:
At first we went through all the tasks given in the shell project pdf and went on to implement each required functionality one by one. 
After each functionality had basic code, we worked on optimizing and modifying the code, as well as implementing further functionalities tagged as intermediate and advanced.

Challenges encountered along the way were mostly confusion on what to do, how to start, how to implement various parts that we did not learn about and had to figure out ourselves with no help.
There were some issues working with files, struggling to access them.
There was also a repeadet issue of the while loop getting ignored and the code ending after only one implementation.

Sources used were in large parts stackOverflow, ChatGPT, as well as various sites holding fragments of c code.



pdf file explaining necessary implementations and tasks;

# OperatingSystemsProject

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
