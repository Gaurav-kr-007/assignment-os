#include <stdio.h> // printf() and scanf()
#include <stdlib.h> // stderr() and NULL
#include <pthread.h> // posix threading

int * array;
int n = 0;

void * fibseries() {
	int x, y, temp, i;
	array = malloc(n * sizeof(int));
	if (array == NULL) {
		fprintf(stderr, "Bad allocation\n");
		exit(1);
	}
	x = 0;
	y = 1;
	for (i = 0; i < n; i++) {
		array[i] = x;
		temp = x + y;
		x = y;
		y = temp;
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	int i, error;
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
	// store command line argument in a global variable
	n = arg;

	// now threading logic
	pthread_t th;
	/*
	int pthread_create(thread_id, attr, start_routine, arg);
	thread_id : stores the ID of the new thread in the buffer pointed to by this pointer
	attr : attributes for creations of thread
	start_routine : function to be run
	arg  : argument passed to the function
	*/
	error = pthread_create(&th, NULL, fibseries, NULL);
	if (error) {
		fprintf(stderr, "could not create thread!!\n");
		return 1;
	}

	/* do something time consuming */

	/*
	int pthread_join(thread_id, retval)
	thread_id : thread variable
	retval : the return value from the execution of function in thread (pointer)
	*/
	error = pthread_join(th, NULL);
	if (error) {
		fprintf(stderr, "could not join thread!!\n");
		return 1;
	}
	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
