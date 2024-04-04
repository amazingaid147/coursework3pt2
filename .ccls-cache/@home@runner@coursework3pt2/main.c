#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>


bool CheckIfSolved (int A,int B ,int X){
  int A1 = A;
  int B1 = B;
  
  int i = 0;
  while (A > 0){
    i ++;
    A = A /10;  
  }
  A = A1;
  for (int j = i-1; j >= 0 ; j--){
    int y = A / pow(10,(j));
    if (X == y){
      return false;
    }
    A = A - (y * pow(10,(j)));
  }
  
  i = 0;
  while (B > 0){
    i ++;
    B = B /10;  
  }
  B = B1;
  for (int j = i-1; j >= 0 ; j--){
    int y = B / pow(10,(j));
    if (X == y){
      
      return false;
    }
    B = B - (y * pow(10,(j)));
  }
return true;
}

void  removeDigit(int X , int N , int* A , int* B){
  int A1 = 0;
  int B1  = N ;
  

  bool ProblemSolved = false;
  while (ProblemSolved == false){
    B1--;
    A1++;
    //printf("%d \n%d" , A1,B1);

    ProblemSolved = CheckIfSolved(A1,B1,X);
  
  }
  *A = A1;
  *B = B1;
  printf("%d \n%d" , A1,B1);
}

int main(void) {
  int N =777777777;
  int X  = 7;
  int A = 235;
  int B  = 345 ;
  removeDigit(X,N,&A,&B);
  }