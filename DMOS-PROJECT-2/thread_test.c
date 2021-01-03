/*
 * thread_test.c
 *
 *  Created on: Oct 5, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */
/* (c) Partha Dasgupta 2009
 permission to use and distribute granted. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ucontext.h>

#include "threads.h"

/* Number of co-routunies to create */
#define NumberOfThreads 3

/* Function prototypes */
void function(void);

/* Global variable to increment */
int global = 0;

/* Function executed by each thread */
void function(void){
	int local = 0;
	while(1) {
		printf("Printing from Function %d global = %d  local = %d\n",Curr_Thread->thread_id ,global,local);
		sleep(1);
		global++; local++;
		printf("Function %d yielding .... global = %d  local = %d\n",Curr_Thread->thread_id ,global,local);
		sleep(1);
		yield();
		printf("function %d remainder\n",Curr_Thread->thread_id );
		sleep(1);
		yield();
	}
}

int main() {
	/* Creation of new Queue */
	ReadyQ=newQueue();
	for(int i=0;i<NumberOfThreads;i++)
		start_thread(function);  /* Creation of Threads */
	run();  /* Run Threads */
	return 0;
}
