/*
 * threads.h
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

#ifndef THREADS_H_
#define THREADS_H_

#include "q.h"

/* Function prototypes */
void start_thread(void (*function)(void));
void run();
void yield();
void printThreadId(node* nodeElement);

/* Global variables to implement scheduler*/
node* ReadyQ;
node* Curr_Thread;
int globalThreadCounter=1;

/* Function to initialize threads
 * @parameters
 * 1. funtion pointer to be executed by thread
 *  */
void start_thread(void (*function)(void)){
	void *stack = malloc(8192);
	TCB_t *tempitem = (TCB_t *)malloc(sizeof(TCB_t));
	init_TCB(tempitem, function, stack, 8192);
	tempitem->thread_id =globalThreadCounter;
	node *pushItem=NewItem(&tempitem);
	AddQueue(&ReadyQ,&pushItem);
	globalThreadCounter++;
}

/* Function to run threads */
void run(){
	Curr_Thread=DelQueue(&ReadyQ);
	ucontext_t parent; // get a place to store the main context, for faking
	getcontext(&parent); // magic sauce
	swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

/* Function to yield from thread */
void yield(){
	TCB_t* presentThreadNode;
	presentThreadNode=NewItem(&Curr_Thread);
	AddQueue(&ReadyQ,&presentThreadNode);
	Curr_Thread=DelQueue(&ReadyQ);
	swapcontext(&(presentThreadNode->context), &(Curr_Thread->context));
}

#endif /* THREADS_H_ */
