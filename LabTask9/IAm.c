//----IAm
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------------------------

//----Define used to create a constant for the max size of the string array
#define MAXQUALITIES 1024

//----Main function to run the program
int main() {
  //----Initialize all variables
  char MyQualities[MAXQUALITIES] = "";
  char input[256];
  char* substr;
  FILE* fp;
//----Open MyQualities file to write in
  fp = fopen("MyQualities.txt", "w");
  if (fp == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }
//----Prompts user to enter sentences
  printf("Please enter sentences, . to end.\n");
  while(1){
//----Take input of sentences, end while loop if "." character is entered
    fgets(input, 256, stdin);
    if (strcmp(input, ".\n") == 0){
      break;
    }
//----Add the qualities that come after "I am" to the string array and put them in the file
    substr = strstr(input, "I am ");
    if (substr != NULL){
      substr += 5;
      strncat(MyQualities, substr, MAXQUALITIES - strlen(MyQualities) -1);
      MyQualities[strcspn(MyQualities, "\n")] = 0;
      strncat(MyQualities, ", ", MAXQUALITIES - strlen(MyQualities) -1);
      fputs(substr, fp);
    }
  }
  fclose(fp);
//----Remove the last comma
  size_t len = strlen(MyQualities);
  if (len > 0 && MyQualities[len - 2] == ','){
    MyQualities[len - 2] = '\0';
  }
//----Print the qualities
  printf("The qualities are %s.\n\n", MyQualities);
//----Open the file for reading and print the qualities again
  fp = fopen("MyQualities.txt", "r");
  printf("Confirming the saved qualities ...\n");
  while(fgets(input, sizeof(input), fp) != NULL){
    input[strcspn(input, "\n")] = 0;
    printf("    %s\n", input);
  }
//----Close and delete the file
  fclose(fp);
  remove("MyQualities.txt");
  return(EXIT_SUCCESS);
} 
