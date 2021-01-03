/*
 * msgs_test.c
 *
 *  Created on: Nov 11, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "msgs.h"

#define NUMBER_OF_PORTS  100
#define NUMBER_OF_MESSAGES_PER_PORT  10
#define LENGETH_OF_MESSAGE  10

#define NUMBER_OF_SERVERS  17
#define NUMBER_OF_CLIENTS  32

void client(void);
void server(void);

Port_t *ports[NUMBER_OF_PORTS];

int clientId=1;
int serverId=1;

Semaphore_t *clientMutex;
Semaphore_t *serverMutex;

int main(){
	ReadyQ = (node*) malloc(sizeof(node));
    ReadyQ=newQueue();

    for(int i=0;i<NUMBER_OF_PORTS;i++){
    	ports[i] = initPort(NUMBER_OF_MESSAGES_PER_PORT,LENGETH_OF_MESSAGE);
    }
    for(int i=0;i<NUMBER_OF_SERVERS;i++){
    	start_thread(server);
    }
    for(int i=0;i<NUMBER_OF_CLIENTS;i++){
    	start_thread(client);
    }
    clientMutex = CreateSem(1);
    serverMutex = CreateSem(1);
   	run();
	while(1);
}

void client(void){
	int myId;
	P(&clientMutex);
	myId = clientId;
	clientId++;
	V(&clientMutex);
	int *data = (int *)malloc(sizeof(int)*LENGETH_OF_MESSAGE);
	for(int i=0;i<LENGETH_OF_MESSAGE;i++)
		data[i] = myId;
	while(1){
		for(int i=0;i<NUMBER_OF_PORTS;i++){
			printf("Client %d is sending data on port %d\n",myId,i+1);
			send(ports[i],data);
		}
	}
}

void server(void){
	int myId;
	P(&serverMutex);
	myId = serverId;
	serverId++;
	V(&serverMutex);
	int *data = (int *)malloc(sizeof(int)*LENGETH_OF_MESSAGE);
	while(1){
		for(int i=0;i<NUMBER_OF_PORTS;i++){
			receive(ports[i],data);
			printf("Server %d received data on port %d received data is",myId,i+1);
			for(int i=0;i<LENGETH_OF_MESSAGE;i++)
				printf(" %d ",data[i]);
			printf("\n");
		}
	}
}

