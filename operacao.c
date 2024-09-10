#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX_NUMBERS 400000000
#define MAX_VALUE 1000
#define NUM_THREADS 2

float numbers[MAX_NUMBERS];
unsigned int i;

struct timeval pop_tabela1, pop_tabela2, update_tabela1, update_tabela2;
double pop_total, update_total;

pthread_t threads[NUM_THREADS];

void *init_numbers(void *threadid){
  long tid;
  tid = (long)threadid;
  int start = tid * (MAX_NUMBERS / NUM_THREADS);
  int end = start + (MAX_NUMBERS / NUM_THREADS);
  gettimeofday(&pop_tabela1, NULL);
  for(i = start; i < end; i++)
    numbers[i] = ((float)rand()/(float)RAND_MAX) * MAX_VALUE;
  gettimeofday(&pop_tabela2, NULL);
  pop_total = (pop_tabela2.tv_sec - pop_tabela1.tv_sec) + ((pop_tabela2.tv_usec - pop_tabela1.tv_usec)/1000000.0);
  pthread_exit(NULL);
}

void *update_numbers(void *threadid){
  long tid;
  tid = (long)threadid;
  int start = tid * (MAX_NUMBERS / NUM_THREADS);
  int end = start + (MAX_NUMBERS / NUM_THREADS);
  gettimeofday(&update_tabela1, NULL);
  for (i = start; i < end; i++){
    numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;    
  }  
  gettimeofday(&update_tabela2, NULL);
  update_total = (update_tabela2.tv_sec - update_tabela1.tv_sec) + ((update_tabela2.tv_usec - update_tabela1.tv_usec)/1000000.0);
  pthread_exit(NULL);
}

int main (int argc, char **argv){
  srand(time(NULL));
  long t;
  for(t=0; t<NUM_THREADS; t++){
    pthread_create(&threads[t], NULL, init_numbers, (void *)t);
  }
  for(t=0; t<NUM_THREADS; t++){
    pthread_join(threads[t], NULL);
  }
  for(t=0; t<NUM_THREADS; t++){
    pthread_create(&threads[t], NULL, update_numbers, (void *)t);
  }
  for(t=0; t<NUM_THREADS; t++){
    pthread_join(threads[t], NULL);
  }
  printf("Populate Table Time: %f\n",pop_total);
  printf("Update Table Time: %f\n",update_total);
  return 0;
}