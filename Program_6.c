/*
============================================================================
Name : Program 6
Author : Hari Prasad C
Description : Write a simple program to create three threads.
Date: 30th Sep, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void thread_func (char *ptr) {
	printf("%s \n", ptr);
}

int main() {
	pthread_t thread1, thread2, thread3;
	char *message1 = "This is Thread1";
	char *message2 = "This is Thread2";
	char *message3 = "This is Thread3";	
	
	pthread_create ( &thread1, NULL, (void *) thread_func, message1 );
	pthread_create ( &thread2, NULL, (void *) thread_func, message2 );
	pthread_create ( &thread3, NULL, (void *) thread_func, message3 );

	pthread_join ( thread1, NULL);
	pthread_join ( thread2, NULL);
	pthread_join ( thread3, NULL);
	
	return 0;
}
