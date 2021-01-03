/*
 * threads.h
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


#ifndef INC_THREADS_H_
#define INC_THREADS_H_

pthread_t start_thread(void *func, void *arg)
{
   pthread_t thread_id;
   int rc;
   printf("In main: creating thread\n");
   rc = pthread_create(&thread_id, NULL, func, arg);
   if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
    }
    return(thread_id);
}

#endif /* INC_THREADS_H_ */
