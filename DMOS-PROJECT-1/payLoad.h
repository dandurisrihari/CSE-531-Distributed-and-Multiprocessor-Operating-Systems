/*
 * payLoad.h
 *
 *  Created on: Sep 21, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */



#ifndef INC_PAYLOAD_H_
#define INC_PAYLOAD_H_

typedef struct payLoad_t{
	int *valueptr;
	semaphore_t *threadLockptr;
}payLoad_t;

#endif /* INC_PAYLOAD_H_ */
