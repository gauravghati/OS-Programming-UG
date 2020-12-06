# OS-Programming

You can't have a CS degree without the knowledge of OS-programming, It is one of the most imp subjects of CS degree, 
Worried about OS-Programming, chill! because we got you covered!

This repo is of Basics of OS-Programming.. 

This book might help to brush up your OS skills - https://doc.lagout.org/operating%20system%20/linux/Beginning%20Linux%20Programming%2C%204%20Ed.pdf

## About Assignments

### 1) Shell Programming
```
Write a program to implement an address book with options given below:
    a) Create address book. 
    b) View address book. 
    c) Insert a record.
    d) Delete a record. 
    e) Modify a record. 
    f) Exit
```
### 2) Process
```
Process  control  system  calls:  The  demonstration  of  FORK,  EXECVE  and  WAIT  system calls along with 
zombie and orphan states.

1.  Implement the C program in which main program accepts the integers to be sorted. Main  program  uses  
the  FORK  system  call  to  create  a  new  process  called  a  child process. Parent process sorts the 
integers using sorting algorithm and waits for child process  using  WAIT  system  call  to  sort  the  
integers  using  any  sorting  algorithm. Also demonstrate zombie and orphan states.

2.  Implement  the  C  program  in  which  main  program  accepts  an  integer  array.  Main program uses 
the FORK system call to create a new process called a child process. Parent  process  sorts  an  integer 
array  and  passes  the  sorted  array  to  child  process through  the  command  line  arguments  of  
EXECVE  system  call.  The  child  process uses  EXECVE  system  callto  load  new  program  that  uses  
this  sorted  array  for performing the binary search to search the particular item in the array.
```
### 3) Threads
```
Matrix Multiplication using POSIX pthreads
```
### 4) Producer Consumer Problem
```
Thread synchronization using counting semaphores
Application to demonstrate producer-consumer problem with counting semaphores and mutex.
Implement  C  program  to  demonstrate producer-consumer  problem  with counting semaphores and mutex.
```

### 5) Reading Writer Problem
```
Thread synchronization and mutual exclusion using mutex.

Implement C program to demonstrate Reader-Writer problem with  readers  having priority using counting 
semaphores and mutex
```

### 6) Dining Philosopher Problem
```
To implement Dining Philosopher’s problem using ‘C’ in Linux

Implement  the  deadlock-free  solution  to  Dining  Philosophers  problem  to illustrate   the   problem   
of   deadlock   and/or   starvation   that   can   occur   when   many synchronized threads are competing 
for limited resources

```

### 7) IPC: Pipes and FIFOs
```
Inter process communication in Linux using pipes: 

A) Implementation of Full duplex communication  between parent and child processes. Parent processwrites  
a  pathname  of  a  file  (the  contents of  the  file  are  desired) on one  pipe  to  be readby child 
process and child process writes the contents of the file on second pipe to beread by parent process and 
displays on standard outpu

B) ImplementationofFull  duplex  communication  between  two  independent  processes.  First processaccepts 
sentences and writes on one pipe to be read by second process and secondprocess  counts number  of  characters, 
number  of  words  and  number  of  lines  in  acceptedsentences, writes this output in a text file and 
writes the contents of the file on secondpipe tobe read by first process and displays on standard output
```

### 8) IPC: Shared Memory
```
Application  to  demonstrate:  Client  and  Server  Programs  in  which  server  process creates  a  shared 
memory segment  and  write  the  message  to  the  shared  memory  segment. Client process  reads  the  
message  from  the shared  memory  segment  and  displays  it  to  the screen.
```

### 7) File Handling

```
File  Handling  System  Calls:  Implement  an  assignment  using  File  Handling  System  Calls (Low level 
system calls like open, read, write, etc)
```
