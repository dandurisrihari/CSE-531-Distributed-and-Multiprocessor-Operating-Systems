/*
 * proj-1.h
 *
 *  Created on: Sep 21, 2020
 *      Author 1: 	Datta Manikanta Srihari
 *      ASU ID: 	1217423272
 *
 *      Author 2: 	Chirra Reddy Sai Sankeerth Reddy
 *      ASU ID: 	1217068242
 */

#ifndef INC_PROJ_1_H_
#define INC_PROJ_1_H_

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void function(void *arg);
pthread_t start_thread(void *func, void *arg);
typedef struct semaphore_t semaphore_t;
void init_sem(semaphore_t *s, int i);
void P(semaphore_t *sem);
void V(semaphore_t * sem);

typedef struct payLoad_t payLoad_t;

#include "semaphores.h"
#include "threads.h"
#include "payLoad.h"

#endif /* INC_PROJ_1_H_ */
