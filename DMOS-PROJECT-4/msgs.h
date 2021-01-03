/*
 * msgs.h
 *
 *  Created on: Nov 11, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */
#ifndef MSGS_H_
#define MSGS_H_

#include "sem.h"
#include <stdlib.h>

/* Function and structure prototypes */
struct Message_t;
struct Port_t;
typedef struct Port_t Port_t;
typedef struct Message_t Message_t;
Port_t * initPort(int numberOfMessagesPerPort,int lengthOfEachMessage);
void send(Port_t *port, int message[]);
void receive(Port_t *port, int message[]);

/* Message_t structure */
struct Message_t{
	int *message;
};

/* Port_t structure */
struct Port_t{
	Semaphore_t* mutex;
	Semaphore_t* removingLock;
	Semaphore_t* fillingLock;
	int in;
	int out;
	Message_t *messages;
	int numberOfMessagesPerPort;
	int lengthOfEachMessage;
};


/* Function to create create and initialize port
 * @parameters
 * 1. number of Messages per port required
 * 2. length of each message in port
 * @return - Pointer to new port
 *  */
Port_t * initPort(int numberOfMessagesPerPort,int lengthOfEachMessage){
	Port_t *port = (Port_t *)malloc(sizeof(Port_t));
	port->mutex = CreateSem(1);
	port->removingLock = CreateSem(0);
	port->fillingLock = CreateSem(numberOfMessagesPerPort);
	port->in = 0;
	port->out = 0;
	port->messages = malloc(sizeof(Message_t)*numberOfMessagesPerPort);
	for(int i=0;i<numberOfMessagesPerPort;i++)
		port->messages[i].message = malloc(sizeof(int)*lengthOfEachMessage);
	port->numberOfMessagesPerPort = numberOfMessagesPerPort;
	port->lengthOfEachMessage = lengthOfEachMessage;
	return port;
}

/* Function to send data to port
 * @parameters
 * 1. Pointer to a port
 * 2. Pointer to an integer array
 *  */
void send(Port_t *port, int message[]){
	P(&port->fillingLock);
		P(&port->mutex);
          for(int i=0;i<(port->lengthOfEachMessage);i++)
        	  port->messages[port->in].message[i] = message[i];
          port->in = (port->in+1) % (port->numberOfMessagesPerPort);
        V(&port->mutex);
	V(&port->removingLock);
}

/* Function to send receive data from port
 * @parameters
 * 1. Pointer to a port
 * 2. Pointer to an integer array
 *  */
void receive(Port_t *port, int message[]){
	P(&port->removingLock);
		P(&port->mutex);
          for(int i=0;i<(port->lengthOfEachMessage);i++)
        	  message[i] = port->messages[port->out].message[i];
          port->out = (port->out+1) % (port->numberOfMessagesPerPort);
        V(&port->mutex);
	V(&port->fillingLock);
}

#endif /* MSGS_H_ */
