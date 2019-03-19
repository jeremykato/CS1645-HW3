#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define FUNCTION(x) ((4) / (1 + (pow(x, 2.0))))
#define DOMAIN_START 0.0
#define DOMAIN_END 1.0

double global_sum, dx;
int iterations_per_thread;
pthread_mutex_t mutex;

void *thread_calculate() {

}

int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    printf("Usage: ./hw3 <Total Trapezoids> <Total Pthreads>\n");
    exit(-1);
  }

  int total_iterations = atoi(argv[1]),
      threads = atoi(argv[2]);

  if (total_iterations < 1 || threads < 1) {
    printf("Error: number of trapezoids and threads must be greater than zero.\n");
    exit(-1);
  }
  else if (total_iterations % threads != 0) {
    printf("Error: number of trapezoids must be evenly divisible by the number of threads.\n");
    exit(-1);
  }

  double domain_start = DOMAIN_START, // start of each thread's domain
         domain_inc   = (DOMAIN_END - DOMAIN_START) / ((double) threads); // distance between domains divided by number of threads
  iterations_per_thread = total_iterations / threads;  // calculate how many iterations each thread performs
  dx = domain_inc / iterations_per_thread; // how much to increase by each iteration

  pthread_mutex_init(&mutex);
  pthread_t *threads = calloc(threads, sizeof(pthread_t));
  double *params = calloc(threads, sizeof(double));

  int p;
  for (p = 0; p < threads; p++) {
    params[p] = domain_start;
    pthread_create((threads + p), NULL, &thread_calculate, (params + p));
  }

  for (p = 0; p < threads; p++) {
    pthread_join((threads + p), NULL);
  }

  printf("Result: %lf", global_sum);

}