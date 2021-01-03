/*
 * proj-1.c
 *
 *  Created on: Sep 21, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */

/* (c) Partha Dasgupta 2009
 permission to use and distribute granted. */

#include "proj-1.h"

/* change the children for different number of threads */
#define children		3
#define ArraySize		children

/* common lock to control all threads */
semaphore_t commonLock;

int main()
{
	/* Dynamic memory allocation of array */
	int *arr=(int *)malloc(sizeof(int)*children);
	memset((void *)arr,0,(size_t )(sizeof(int)*children));
    if(arr==NULL){
    	printf("Array memory not allocated");
    	return 0;
    }

    /* Dynamic memory allocation of locks for individual threads */
    semaphore_t *locks=(semaphore_t *)malloc(sizeof(semaphore_t)*children);
    if(locks==NULL){
    	printf("locks memory not allocated");
    	return 0;
    }

    /* Dynamic memory allocation of payLoad to send to threads */
	payLoad_t *load=(payLoad_t *)malloc(sizeof(payLoad_t)*children);
    if(load==NULL){
    	printf("load memory not allocated");
    	return 0;
    }

    /* initialization of locks */
    init_sem(&commonLock,children);
    for(int i=0;i<children;i++){
    	init_sem(&locks[i], 1);
    	load[i].threadLockptr=&locks[i];
    	load[i].valueptr=&arr[i];

    }

    /* starting of threads */
    for(int i=0;i<children;i++)
    	start_thread(function,((void *)&load[i]));

    while(1)
    {
	   if(commonLock.count==0){
	   		for(int i=0;i<children;i++){
	   			printf("arr[%d]=%d\t",i,arr[i]);
	   			/* release of locks */
	   			V(load[i].threadLockptr);
	   			V(&commonLock);
	   		}
	   		//sleeping to observe the output
	   		usleep(1000);
	   		printf("\n");
       }
    }

    return 0;
}

/*function executed by threads */
void function(void *arg)
{
    while (1){
    	payLoad_t *ptr =(payLoad_t *)arg;
        P(ptr->threadLockptr);
		*(ptr->valueptr)=*(ptr->valueptr)+1;
		P(&commonLock);
    }
}
