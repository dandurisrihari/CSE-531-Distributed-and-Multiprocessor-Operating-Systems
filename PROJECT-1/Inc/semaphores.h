/*
 * semaphores.h
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

#ifndef INC_SEMAPHORES_H_
#define INC_SEMAPHORES_H_

typedef struct semaphore_t {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     int count;
} semaphore_t;

void init_sem(semaphore_t *s, int i)
{
    s->count = i;
    pthread_mutex_init(&(s->mutex), NULL);
    pthread_cond_init(&(s->cond), NULL);
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process
 */
void P(semaphore_t *sem)
{
    pthread_mutex_lock (&(sem->mutex));
    sem->count--;
    if (sem->count < 0) pthread_cond_wait(&(sem->cond), &(sem->mutex));
    pthread_mutex_unlock (&(sem->mutex));
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */

void V(semaphore_t * sem)
{
    pthread_mutex_lock (&(sem->mutex));
    sem->count++;
    if (sem->count <= 0) {
	pthread_cond_signal(&(sem->cond));
    }
    pthread_mutex_unlock (&(sem->mutex));
    pthread_yield();
}

#endif /* INC_SEMAPHORES_H_ */
