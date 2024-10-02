//----NewSpecies
//--------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------------------------

//----Typedef used to create enum for type of animal
typedef enum {
  MAMMAL,
  INSECT,
  BIRD,
  FISH
} AnimalType;

//----Typedef to create a struct to hold the animal name, size, and type
typedef struct {
  char name[128];
  double size;
  AnimalType type;
} species;

//----Main function to run the program
int main() {
  //----Create variable size for the inital size of the array
  //----Create variable NumberOfSpecies for the initial number of species in the array
  //----Malloc space in the array for the first species
  int size = 1;
  int NumberOfSpecies = 0;
  species *SpeciesArray = malloc(sizeof(species)*size);
  
  if(SpeciesArray == NULL){
    printf("Error: malloc failed.\n");
    exit(1);
  }

  //----Take input of animal name, size, and type
  printf("NewSpecies\n");
  while(1){
    printf("Enter animal information (\"exit\" to exit)\n");
    printf("What is the name : ");
    char name[128];
    fgets(name, 128, stdin);
    name[strcspn(name, "\n")] = '\0';

    if(strcmp(name, "exit") == 0) {
      break;
    }

    printf("What is the size : ");
    double size;
    scanf("%lf", &size);
    getchar();

    printf("What is the type : ");
    char TypeStr[128];
    fgets(TypeStr, 128, stdin);
    TypeStr[strcspn(TypeStr, "\n")] = '\0';

    AnimalType type;
    if (strcmp(TypeStr, "mammal") == 0){
      type = MAMMAL;
    }
    else if (strcmp(TypeStr, "insect") == 0){
      type = INSECT;
    }
    else if (strcmp(TypeStr, "bird") == 0){
      type = BIRD;
    }
    else if (strcmp(TypeStr, "fish") == 0){
      type = FISH;
    }
    else {
      printf("Error: invalid animal type.\n");
      continue;
    }
    
    //----Expand the size of the array using realloc if number of species equals size
    if(NumberOfSpecies == size){
      size *=2;
      species *NewArray = realloc(SpeciesArray, sizeof(species) * size);
      
      if(NewArray == NULL){
        printf("Error: realloc failed.\n");
        exit(1);
      }
      
      SpeciesArray = NewArray;
    }

    //----Input species name, size, and type into an element of the array
    strncpy(SpeciesArray[NumberOfSpecies].name, name, 128);
    SpeciesArray[NumberOfSpecies].size = size;
    SpeciesArray[NumberOfSpecies].type = type;
    NumberOfSpecies++;
  }

  //----Print out the species name, size, and type
  printf("The following new species were found:\n");
  for(int i = 0; i < NumberOfSpecies; i++){
    printf("%-20s has size %6.2f and is a ", SpeciesArray[i].name, SpeciesArray[i].size);
    switch (SpeciesArray[i].type){
      case MAMMAL:
        printf("mammal\n");
        break;
      case INSECT:
        printf("insect\n");
        break;
      case BIRD:
        printf("bird\n");
        break;
      case FISH:
        printf("fish\n");
        break;
    }
  }
  //----Free the memory
  free(SpeciesArray);

  return (EXIT_SUCCESS);
}










