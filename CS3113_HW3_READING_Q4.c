#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>

#define NUMBER_OF_THREADS 10 /*number of threads that need to be created*/
#define SUM_TO 1000

long thread_sums[NUMBER_OF_THREADS]; /*sums done by each thread*/
void *runner(void *param); /*function for threads to use*/

int main(int argc, char *argv[]){
    pthread_t thread_listings[NUMBER_OF_THREADS]; /*array for the 10 pthreads*/
    int ids_of_threads[NUMBER_OF_THREADS]; /*ids or titles of threads (0-9)*/

    for (int i = 0; i < NUMBER_OF_THREADS; i++){ /*create the 10 threads*/
        ids_of_threads[i] = i;
        pthread_create(&thread_listings[i],NULL,runner,&ids_of_threads[i]);
    }

    for (int i = 0; i < NUMBER_OF_THREADS; i++){ /*join/run through threads one by one*/
        pthread_join(thread_listings[i],NULL);
    }

    long total_sum = 0; /*add up the sums of the threads*/
    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        total_sum += thread_sums[i];
    }
    printf("the total sum of 0 to 9999 is = %ld\n",total_sum);

    return 0;
}

void *runner(void *param){
    int current_thread_id = *(int*)param;
    int start = current_thread_id * SUM_TO;
    int end = start + SUM_TO;

    long current_thread_total = 0;
    for(int i = start; i < end; i++){
        current_thread_total += i;
    }
    printf("the current thread %d has been summed to: %ld\n", current_thread_id, current_thread_total);
    thread_sums[current_thread_id] = current_thread_total;
    pthread_exit(0);
}