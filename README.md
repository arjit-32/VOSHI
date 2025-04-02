# VOSHI - Visual Operating System Handling Interface


Rough Notes: 
- fork() command is creating a new child process ( exact copy of parent). Both run independently, can use `wait` to get a bit deterministic.
- execvp command replaces current process with new program, essentially changing the program.
- cd is not a system command
- perror is used for system calls related erros
- Singal Handling: A interrupt that is sent to running process by kernel, ex - CTRL+Z which generates SIGINT. Can make custom signal handler using `signal` function.

---
Resource - 
https://igupta.in/blog/writing-a-unix-shell-part-2/