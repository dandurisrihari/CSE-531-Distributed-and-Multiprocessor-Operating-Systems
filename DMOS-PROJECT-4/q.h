/*
 * q.h
 *
 *  Created on: Oct 5, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */

#ifndef Q_H_
#define Q_H_

#include <stdio.h>
#include <stdlib.h>

#include "TCB.h"

/* Prototypes */
typedef TCB_t node;
node* NewItem(node** TCB_ItemDataPtr);
node* newQueue(void);
void AddQueue(node** Queuehead,node** item);
node* DelQueue(node** Queuehead);

/* Function to generate new item to place in ReadyQ from Data given
 *  @parameters
 *  1. address of TCB item data pointer
 *  */
node* NewItem(node** TCB_ItemDataPtr){
	node *itemNodePtr=(node *)malloc(sizeof(node));
	itemNodePtr->thread_id =(*TCB_ItemDataPtr)->thread_id ;
	itemNodePtr->context=(*TCB_ItemDataPtr)->context;
	itemNodePtr->next=NULL;
	itemNodePtr->previous=NULL;
	free((*TCB_ItemDataPtr));
	return itemNodePtr;
}

/* Function to generate new Queue */
node* newQueue(){
	node *headPtr=NULL;
	return headPtr;
}

/* Function to add items in to Queue
 * @parameters
 * 1. address of Queue head pointer
 * 2. address of item pointer
 *  */
void AddQueue(node** Queuehead,node** item){
	node *itemNodePtr=*item;
	if((*Queuehead)==NULL){			/* check if Queue is empty */
		(*Queuehead)=itemNodePtr;
		(*Queuehead)->next=itemNodePtr;
		(*Queuehead)->previous=itemNodePtr;
	}
	else{                           /* If not empty add element at the end of Queue */
		node *currentPtr=(*Queuehead);
		do
		{currentPtr=currentPtr->next;}while(currentPtr->next!=(*Queuehead));
		(*Queuehead)->previous=itemNodePtr;
		itemNodePtr->next=(*Queuehead);
		currentPtr->next=itemNodePtr;
		itemNodePtr->previous=currentPtr;
	}
}

/* Function to delete items from Queue
 * @parameters
 * 1. address of Queue head pointer
 *  */
node* DelQueue(node** Queuehead){
	if((*Queuehead)==NULL){       	/* check if Queue is empty if empty raise a error flag */
		printf("Queue is already empty!! trying to delete en element from empty Queue\n");
		exit(-1);
		return (*Queuehead);
	}
	else{
		node *temp=(*Queuehead)->next;
		node *current=(*Queuehead);
		if((*Queuehead)==temp){  (*Queuehead)=NULL;  return current;}	/* check if Queue has only one element */
		temp->previous=(*Queuehead)->previous;			/* if Queue has more than one element remove element pointed by head */
		(*Queuehead)->previous->next=temp;
		(*Queuehead)=temp;
		return current;
	}
}

#endif /* Q_H_ */




