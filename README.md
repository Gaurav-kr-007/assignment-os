# assignment-os
fibonacci series and collatz sequence using operating system concepts

## Collatz sequence

C program using the fork() system call that generates Collatz sequence
in the child process

### Collatz conjecture

Consider the following operation on an arbitrary positive integer:
- If the number is even, divide it by two.
- If the number is odd, triple it and add one.

In short apply the following function repeatedly:
{{image}}

The conjecture states that when this algorithm is continually applied,
all positive integers will eventually reach 1.

**Example**: For `n = 35`
```
35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1
```

### OS Process concept

The starting number will be provided from the command line.
After calling fork(), the child process shall output the
collatz sequence. The parent has to wait for the child process
to complete and then exit the program.

The program also performs error checking to verify that
a positive integer is passed through command line.

