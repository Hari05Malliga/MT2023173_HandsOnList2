/*
============================================================================
Name : Program 7
Author : Hari Prasad C
Description : Write a simple program to print the created thread ids.
Date: 30th Sep, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void thread_func (void) {
	printf("Thread ID : %ld\n", pthread_self());
}

int main() {
	pthread_t thread1, thread2, thread3;
	
	pthread_create ( &thread1, NULL, (void *) thread_func, NULL );
	pthread_create ( &thread2, NULL, (void *) thread_func, NULL );
	pthread_create ( &thread3, NULL, (void *) thread_func, NULL );

	pthread_join ( thread1, NULL);
	pthread_join ( thread2, NULL);
	pthread_join ( thread3, NULL);
	
	return 0;
}
