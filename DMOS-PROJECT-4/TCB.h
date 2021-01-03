/*
 * TCB.h
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

#ifndef TCB_H_
#define TCB_H_

#include <ucontext.h>
#include <string.h>

/* Prototypes */
struct TCB_t;
typedef struct TCB_t TCB_t;
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size);

/* TCB_t structure */
struct TCB_t{
	ucontext_t context;
	int thread_id ;
	TCB_t *next;
	TCB_t *previous;
};

/* Function to initialize TCB */
void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size){
	memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
	getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
	tcb->context.uc_stack.ss_sp = stackP;
	tcb->context.uc_stack.ss_size = (size_t) stack_size;
	makecontext(&tcb->context, function, 0);// context is now cooked
}

#endif /* TCB_H_ */
