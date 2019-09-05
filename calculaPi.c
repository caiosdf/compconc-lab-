#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <pthread>
//#include <unistd>

long long int numElement;

void calculaPi(int n){
  double pi = 1.0;
  int i;
  for(i = 0; i < n; i++){
    pi += (pow(-1,i+1))*(1.0/(2.0*(i+1)+1.0));

  }
  pi = 4*pi;
  printf("%lf\n", pi);
}

int main (int argc, char **argv){

  numElement = atoll(argv[1]);
  calculaPi(numElement);

  return 0;
}
