#include <stdio.h>
#include <stdlib.h>
//the function takes in an array filled with coefficients of length n and calculates the polynomial on the given x
//this array is sorted by decreasing order of exponent with a decrement of 1
//for example, 4x^2 + 2x^3 + 5 would be polynomial((int*){2,4,0,5}, 4, x)
//the exponent 3 is the greatest (hence 2 in front) and there is no coefficient of x^1 (hence the 0)
float polynomial(int *arr, int n, float x){
  if(n<1) return 0; //should return error, there is no polynomial basically
  float prev=arr[0];
  int i;
  for(i=1;i<n;i++)
    prev=(prev*x)+arr[i];
  return prev;
}

int main(){
  int *coefficients=(int*)malloc(sizeof(int)*4);
  coefficients[0] = 2;
  coefficients[1] = 4;
  coefficients[2] = 0;
  coefficients[3] = 5;
  printf("%.2f",polynomial(coefficients, 4, 3));
  return 0;
}
