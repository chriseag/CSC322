#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *PointerToInt;
int IntArray[5];
int *ArrOfPointersToInts[5];

typedef int* IntPointer;

void InitializeIntArrayElements(int * arr){
  //srand(getpid());
  //for(int i = 0; i < 5; i++){
   //arr[i] = rand();
  //}

  arr[0] = 958486403;
  arr[1] = 1006139074;
  arr[2] = 893180240;
  arr[3] = 769601150;
  arr[4] = 392522169;
}

void InitializePointerArrayElements(IntPointer* arr, int * intArr){
  for(int i = 0; i < 5; i++) {
    arr[i] = &intArr[i];
  }
}
  
void PrintIntArray(int * arr){
  for(int i = 0; i < 5; i++){
    printf(" %d : %d\n", i, arr[i]);
  }
}

void PrintPointerArray(IntPointer* arr){ 
  for(int i = 0; i < 5; i++){
    printf(" %d : %d\n", i, *arr[i]);
  }
}

void BubbleSortIntArray(int * arr){
  int temp;
  for(int i = 0; i < 5-1; i++){
    for(int j = 0; j < 5-i-1; j++){
      int *point1 = (arr + j);
      int *point2 = (arr + j + 1);
      if(*point1>*point2){
        temp = *point1;
        *point1 = *point2;
        *point2 = temp;
      }
    }
  }
}

void BubbleSortPointerArray(IntPointer* arr){
  int temp;
  for(int i = 0; i < 5-1; i++){
    for(int j = 0; j < 5-i-1; j++){
      int *point1 = (*arr + j);
      int *point2 = (*arr + j + 1);
      if(*point1>*point2){
        temp = *point1;
        *point1 = *point2;
        *point2 = temp;
      }
    }
  }
}

int main(void){
  int IntArr[5];
  IntPointer PointerArray[5];

   
  InitializeIntArrayElements(IntArr);
  InitializePointerArrayElements(PointerArray, IntArr);
  
  printf("---- Initialized array of integers ----\n");
  PrintIntArray(IntArr);
  
  BubbleSortPointerArray(PointerArray);
  
  printf("---- Sorted array of pointers ----\n");
  PrintPointerArray(PointerArray);

  BubbleSortIntArray(IntArr);

  printf("---- Sorted array of integers ----\n");
  PrintIntArray(IntArr);

  printf("---- Array of pointers ----\n");
  PrintPointerArray(PointerArray);

  return (EXIT_SUCCESS);

}
