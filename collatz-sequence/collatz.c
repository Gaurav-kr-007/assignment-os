#include <stdio.h> // printf() and scanf()
#include <stdlib.h> // stderr and atoi()
#include <unistd.h> // fork() and pid_t
#include <wait.h> // wait()

// function prints collatz sequence
void czseq(int n) {
	while (n > 1) {
		printf("%d ", n);
		if (n&1) {
			// if odd
			n = 3*n + 1;
		} else {
			// if even, then halve it
			n = n >> 1; // n/2
		}
	}
	printf("%d\n", n);
}

int main(int argc, char* argv[]) {
	// validate command line arguments
	if (argc <= 1) {
		fprintf(stderr, "No command line argument supplied\n");
		return 1;
	}
	if (argc > 2) {
		fprintf(stderr, "too many command line arguments\n");
		return 1;
	}
	int arg = atoi(argv[1]);
	if (arg <= 0) {
		fprintf(stderr, "invalid argument!! Please supply a positive integer\n");
		return 1;
	}
	// now everything is valid
	// create child and call `czseq`

	// printf("Starting child...\n");
	pid_t pid = fork();
	// on success pid of child process is returned to parent
	// and 0 is returned to the child
	// -1 is returned on error
	if (pid == -1) {
		fprintf(stderr, "error creating child process\n");
		return 1;
	}
	if (pid == 0) { // then child
		czseq(arg);
	} else { // then parent
		// suspends execution until one of its children terminates
		pid = wait(NULL);
		// wait returns pid of terminated child upon success
		// or returns -1 on failure
		if (pid == -1) {
			fprintf(stderr, "child exited abnormally\n");
		}
		// printf("Child with pid %d terminated normally\n", pid);
	}
	return 0;
}
