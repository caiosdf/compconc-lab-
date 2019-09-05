#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
//#include <unistd>

long long int numElement;
int numThreads;
double piFinal;

void calculaPi(void *tid){
  double *ret;
  ret = malloc(sizeof(double));
  double pi = 1.0;
  int i = *(int *) tid;
  for(; i < numElement; i += numThreads){
    pi += (pow(-1,i+1))*(1.0/(2.0*(i+1)+1.0));

  }
  //pi = 4*pi;
  //printf("%lf\n", pi);

  *ret = pi;
  free(tid);
  pthread_exit((void*) ret);
}

int main (int argc, char **argv){

  pthread_t *tid_sistema;
  int *tid;
  int t;

  double *retorno;
  retorno = malloc(sizeof(double));

  numElement = atoll(argv[1]);
  numThreads = atoi(argv[2]);

  if(numThreads > numElement){
    numThreads = numElement;
  }

  tid_sistema = (pthread_t*)malloc(sizeof(pthread_t)*numThreads);
  if(tid_sistema == NULL){
    printf("--ERRO: malloc()\n", );
    exit(-1);
  }

  for(t = 0; t < numThreads; t++){
    tid = malloc(sizeof(int));
    if(tid == NULL){
      printf("--ERRO: malloc()\n");
      exit(-1);
    }
    *tid = t;
    if(pthread_create(&tid_sistema[t],NULL,calculaPi,(void*) tid)){
      printf("--ERRO: pthread_create()\n", );
      exit(-1);
    }
  }

  for( t = 0; t < numThreads; t++){
    pthread_join(tid_sistema[t], (void*) &retorno);
    piFinal += *retorno;
  }

  piFinal = 4*piFinal;
  printf("%lf\n", piFinal);

  return 0;
}
