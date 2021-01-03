/*
 * sem.h
 *
 *  Created on: Oct 24, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */

#ifndef SEM_H_
#define SEM_H_

#include "threads.h"

/* Prototypes */
struct Semaphore_t;
typedef struct Semaphore_t Semaphore_t;
void V(Semaphore_t **sem);
void P(Semaphore_t **sem);

/* Semaphore structure
 *  */
struct Semaphore_t {
	int count;
	node* TCB_queue;
};

/* Function to create new semaphore
 * @parameters
 * 1. count value of the semaphore
 *  */
Semaphore_t* CreateSem(int InputValue){
	Semaphore_t *semaPtr=(Semaphore_t *)malloc(sizeof(Semaphore_t));
	semaPtr->count=InputValue;
	semaPtr->TCB_queue=newQueue();
	return semaPtr;
}

/* Function to acquire the semaphore
 * @parameters
 * 1. address of the semaphore variable
 *  */
void P(Semaphore_t **sem){
	(*sem)->count-=1;
	if((*sem)->count<0)
	{
		node* presentThreadNode;
		presentThreadNode=NewItem(&Curr_Thread);
		AddQueue(&(*sem)->TCB_queue,&presentThreadNode);
		Curr_Thread=DelQueue(&ReadyQ);
		swapcontext(&(presentThreadNode->context), &(Curr_Thread->context));
	}
}

/* Function to release the semaphore
 * @parameters
 * 1. address of the semaphore variable
 *  */
void V(Semaphore_t **sem){
	(*sem)->count+=1;
	if((*sem)->count<=0)
	{
		node *waitingSemaThread;
		waitingSemaThread=DelQueue(&(*sem)->TCB_queue);
		if(waitingSemaThread!=NULL)
			AddQueue(&ReadyQ,&waitingSemaThread);
	}
	yield();
}

#endif /* SEM_H_ */
