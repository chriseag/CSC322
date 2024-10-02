//----Making Movies
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//--------------------------------------------------------------------------------------------------

typedef int* IntPointer;

IntPointer PointerToInt;
int IntArray[5];
IntPointer ArrOfPointersToInts[5];

//----This function initializes the integer array to 5 random seeded numbers
void InitializeIntArrayElements(int IntArr[5]){
  srand(getpid());
  for(int i = 0; i < 5; i++){
   IntArr[i] = rand();
  }
}

//----This function initializes the pointer array to pointers to the 5 integers in the other array
void InitializePointerArrayElements(IntPointer PointArr[5], int IntArr[5]){
  for(int i = 0; i < 5; i++) {
    PointArr[i] = &IntArr[i];
  }
}

//----This function prints the integer array  
void PrintIntArray(int IntArr[5]){
  for(int i = 0; i < 5; i++){
    printf(" %d : %d\n", i, IntArr[i]);
  }
}

//----This function prints the pointer array
void PrintPointerArray(IntPointer IntArr[5]){ 
  for(int i = 0; i < 5; i++){
    printf(" %d : %d\n", i, *IntArr[i]);
  }
}

//----This function sorts the integer array using bubble sort
void BubbleSortIntArray (int IntArr[5]){
  int temp;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 5-i-1; j++){
      if(IntArr[j] > IntArr[j+1]){
        temp = IntArr[j];
        IntArr[j] = IntArr[j+1];
        IntArr[j+1] = temp;
      }
    }
  }
}

//----This function sorts the pointer array using bubble sort
void BubbleSortPointerArray(IntPointer PointerArray[5]){
  int* temp;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 5-i-1; j++){
      if(*PointerArray[j] > *PointerArray[j+1]){
        temp = PointerArray[j];
        PointerArray[j] = PointerArray[j+1];
        PointerArray[j+1] = temp;
      }
    }
  }
}

//----This function declares an array of 5 integers and an array of 5 integer pointers
//----This function also runs all other functions(initilization, sorting, printing)
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
