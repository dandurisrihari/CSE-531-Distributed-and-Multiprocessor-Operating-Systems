/*
 * proj-1.c
 *
 *  Created on: Sep 21, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 */


// (c) Partha Dasgupta 2009
// permission to use and distribute granted.

#include "../Inc/proj-1.h"

#define children		3
#define ArraySize		children

semaphore_t commonLock;

void function(void *arg)
{
    while (1){
    	payLoad_t *ptr =(payLoad_t *)arg;
        P(ptr->threadLockptr);
		*(ptr->valueptr)=*(ptr->valueptr)+1;
		P(&commonLock);
    }
}
int main()
{
	int *arr=(int *)malloc(sizeof(int)*children);
	memset((void *)arr,0,(size_t )(sizeof(int)*children));
    if(arr==NULL){
    	printf("Array memory not allocated");
    	return 0;
    }
    semaphore_t *locks=(semaphore_t *)malloc(sizeof(semaphore_t)*children);
    if(locks==NULL){
    	printf("locks memory not allocated");
    	return 0;
    }

	payLoad_t *load=(payLoad_t *)malloc(sizeof(payLoad_t)*children);
    if(load==NULL){
    	printf("load memory not allocated");
    	return 0;
    }

    init_sem(&commonLock,children);

    for(int i=0;i<children;i++){
    	init_sem(&locks[i], 1);
    	load[i].threadLockptr=&locks[i];
    	load[i].valueptr=&arr[i];

    }

    for(int i=0;i<children;i++)
    	start_thread(function,((void *)&load[i]));

    while(1)
    {
	   if(commonLock.count==0){
	   		for(int i=0;i<children;i++){
	   			printf("arr[%d]=%d\t",i,arr[i]);
	   			V(load[i].threadLockptr);
	   			V(&commonLock);
	   		}
	   		printf("\n");
       }
       sleep(1);
    }

    return 0;
}
