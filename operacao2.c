#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

//#define IMPRIME

#define MAX_NUMBERS 500000000
//#define MAX_NUMBERS 10
#define MAX_VALUE 1000;
#define NUM_THREADS 4

float numbers[MAX_NUMBERS];
unsigned int i;

void* init_numbers(void* arg){
    int start = *(int*)arg;
    int end = start + MAX_NUMBERS / NUM_THREADS;
    for(int i = start; i < end; i++)
        numbers[i] = ((float)rand()/(float)(RAND_MAX)) * MAX_VALUE;
    return NULL;
}

int show_numbers(){
  for (i = 0; i < MAX_NUMBERS; i++)
    printf("number[%u] = %f\n",i,numbers[i]);
  return 0;
}

int main (int argc, char **argv){
    struct timeval pop_tabela1, pop_tabela2, update_tabela1, update_tabela2;
    double pop_total, update_total;
		pthread_t threads[NUM_THREADS];
    int starts[NUM_THREADS];
  
  srand(time(NULL));

  gettimeofday(&pop_tabela1, NULL);
	for(int i = 0; i < NUM_THREADS; i++){
			starts[i] = i * MAX_NUMBERS / NUM_THREADS;
			pthread_create(&threads[i], NULL, init_numbers, &starts[i]);
	}
	for(int i = 0; i < NUM_THREADS; i++){
			pthread_join(threads[i], NULL);
	}
  gettimeofday(&pop_tabela2, NULL);
  pop_total = (pop_tabela2.tv_sec - pop_tabela1.tv_sec) + ((pop_tabela2.tv_usec - pop_tabela1.tv_usec)/1000000.0);

  #ifdef IMPRIME
    show_numbers();
  #endif
  gettimeofday(&update_tabela1, NULL);
  for (i = 0; i < MAX_NUMBERS; i++){
    numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;    
  }
  gettimeofday(&update_tabela2, NULL);
	update_total = (update_tabela2.tv_sec - update_tabela1.tv_sec) + ((update_tabela2.tv_usec - update_tabela1.tv_usec)/1000000.0);

  #ifdef IMPRIME
    printf("Apos a operacao matematica\n"); 
    show_numbers();
  #endif

  printf("Populate Table Time: %f\n",pop_total);
  printf("Update Table Time: %f\n",update_total);
  return 0;
}