#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//#define IMPRIME

#define MAX_NUMBERS 500000000
//#define MAX_NUMBERS 10
#define MAX_VALUE 1000;

float numbers[MAX_NUMBERS];
unsigned int i;

int init_numbers(){
  for(i = 0; i < MAX_NUMBERS; i++)
    numbers[i] = ((float)rand()/(float)RAND_MAX) * MAX_VALUE;
  return 0;
}

int show_numbers(){
  for (i = 0; i < MAX_NUMBERS; i++)
    printf("number[%u] = %f\n",i,numbers[i]);
  return 0;
}

int main (int argc, char **argv){
  struct timeval t1, t2; 
  
  srand(time(NULL));
 
  init_numbers();

  #ifdef IMPRIME
    show_numbers();
  #endif
 
  for (i = 0; i < MAX_NUMBERS; i++){
    numbers[i] =  numbers[i]*0.2 + numbers[i]/0.3;    
  }  

  #ifdef IMPRIME
    printf("Apos a operacao matematica\n"); 
    show_numbers();
  #endif

  printf("Total time: %f\n",t_total);
  return 0;
}