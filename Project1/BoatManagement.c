//----BoatManagement
//--------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 128
#define MAX_BOATS 120

//--------------------------------------------------------------------------------------------------

//----Enum used to store the location of each boat
typedef enum {SLIP, LAND, TRAILOR, STORAGE} BoatLocation;

//----Typedef (union) used to store the boat location information
typedef union {
  int slipNum;
  char bayLetter;
  char trailorTag[7];
  int storageNum;
} BoatLocationInfo;

//----Typedef used to store the various information for each boat
typedef struct {
  char name[MAX_NAME_LEN];
  int length;
  BoatLocation type;
  BoatLocationInfo location;
  float amountOwed;
} Boat;

//----Array to hold the pointers to each boat is created
Boat *boats[MAX_BOATS];
int numBoats = 0;

//--------------------------------------------------------------------------------------------------
//----Function to load the csv file into the program and load the boats into the array
void loadInventory(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }

  char buffer[MAX_NAME_LEN + 100];
  while (fgets(buffer, MAX_NAME_LEN + 100, fp)) {
    if(numBoats >= MAX_BOATS) {
      break;
    }


    char *name = strtok(buffer, ",");
    int length = atoi(strtok(NULL, ","));
        
    BoatLocation type;
    char *typeStr = strtok(NULL, ",");
    if (strcmp(typeStr, "slip") == 0) {
      type = SLIP;
    } 
    else if (strcmp(typeStr, "land") == 0) {
      type = LAND;
    } 
    else if (strcmp(typeStr, "trailor") == 0) {
      type = TRAILOR;
    } 
    else if (strcmp(typeStr, "storage") == 0) {
      type = STORAGE;
    }
    else {
      printf("Invalid boat type %s\n", typeStr);
      continue;
    }        

    BoatLocationInfo location;
    switch (type) {
      case SLIP:
        location.slipNum = atoi(strtok(NULL, ","));
        break;
      case LAND:
        location.bayLetter = strtok(NULL, ",")[0];
        break;
      case TRAILOR:
        strcpy(location.trailorTag, strtok(NULL, ","));
        break;
      case STORAGE:
        location.storageNum = atoi(strtok(NULL, ","));
        break;
      }
    float amountOwed = atof(strtok(NULL, ","));

    Boat *boat = (Boat *)malloc(sizeof(Boat));
    if (boat == NULL) {
      printf("Error allocating memory for boat\n");
      break;
    }

    strcpy(boat->name, name);
    boat->length = length;
    boat->type = type;
    boat->location = location;
    boat->amountOwed = amountOwed;

    boats[numBoats++] = boat;
  }

  int close_result = fclose(fp);
  if(close_result == EOF) {
    printf("Error closing file\n");
  }
}

//--------------------------------------------------------------------------------------------------
//----Helper function for the qsort
int compareBoatNames(const void *a, const void *b) {
  const Boat *boatA = *(const Boat **)a;
  const Boat *boatB = *(const Boat **)b;
  return strcasecmp(boatA->name, boatB->name);
}

//--------------------------------------------------------------------------------------------------
//----Function to print the boats and their information (in alphabetical order using qsort)
void printInventory(Boat *boats[]) {
  qsort(boats, numBoats, sizeof(Boat *), compareBoatNames);

  for (int i = 0; i < numBoats; i++) {
    if (boats[i] != NULL) {
      printf("%-18s", boats[i]->name);
      printf("%6d'", boats[i]->length);
      switch (boats[i]->type) {
        case SLIP:
          printf("%13s", "slip");
          printf("   ");
          printf(" # %3d", boats[i]->location.slipNum);
          break;
        case LAND:
          printf("%13s", "land");
          printf("   ");
          printf("%6c", boats[i]->location.bayLetter);
          break;
        case TRAILOR:
          printf("%13s", "trailor");
          printf("   ");
          printf("%6s", boats[i]->location.trailorTag);
          break;
        case STORAGE:
          printf("%13s", "storage");
          printf("   ");
          printf(" # %3d", boats[i]->location.storageNum);
          break;
        }
      printf("   Owes $%4.2f\n", boats[i]->amountOwed);
    }
  }
}

//--------------------------------------------------------------------------------------------------
//----Function to add a boat to the array
void addBoat() {
  if (numBoats >= MAX_BOATS) {
    printf("The inventory is full.\n");
    return;
  }

  char boatString[MAX_NAME_LEN + 100];
  printf("Please enter the boat data in CSV format: ");
  scanf("%s", boatString);
  getchar();

  char *name = strtok(boatString, ",");
  int length = atoi(strtok(NULL, ","));
  BoatLocation type;
  char *typeStr = strtok(NULL, ",");
  if (strcmp(typeStr, "slip") == 0) {
    type = SLIP;
  } 
  else if (strcmp(typeStr, "land") == 0) {
    type = LAND;
  } 
  else if (strcmp(typeStr, "trailor") == 0) {
    type = TRAILOR;
  }
  else if (strcmp(typeStr, "storage") == 0) {
    type = STORAGE;
  } else {
    printf("Invalid boat type %s\n", typeStr);
    return;
  }
  BoatLocationInfo location;
  switch (type) {
    case SLIP:
      location.slipNum = atoi(strtok(NULL, ","));
      break;
    case LAND:
      location.bayLetter = strtok(NULL, ",")[0];
      break;
    case TRAILOR:
      strcpy(location.trailorTag, strtok(NULL, ","));
      break;
    case STORAGE:
      location.storageNum = atoi(strtok(NULL, ","));
      break;
  }
  float amountOwed = atof(strtok(NULL, ","));

  Boat *boat = (Boat *) malloc(sizeof(Boat));
  if (boat == NULL) {
    printf("Error: Failed to allocate memory for boat.\n");
    return;
  }

  strcpy(boat->name, name);
  boat->length = length;
  boat->type = type;
  boat->location = location;
  boat->amountOwed = amountOwed;

  boats[numBoats++] = boat;

}

//--------------------------------------------------------------------------------------------------
//----Function to remove a boat from the array
void remove_boat() {
  char name[MAX_NAME_LEN];
  printf("Please enter the boat name: ");
  getchar();
  fgets(name, MAX_NAME_LEN, stdin);
  name[strcspn(name, "\n")] = 0;

  int i;
  for (i = 0; i < numBoats; i++) {
    if (boats[i] != NULL && strcasecmp(boats[i]->name, name) == 0) {
      free(boats[i]);
      boats[i] = boats[numBoats-1];
      boats[numBoats-1] = NULL;
      numBoats--;
      return;
    }
  }
  printf("No boat with that name\n");
}

//--------------------------------------------------------------------------------------------------
//----Function to accept payment for a user-specified boat
void acceptPayment(Boat **boats) {
  char name[MAX_NAME_LEN];
  printf("Please enter the boat name: ");
  getchar();
  fgets(name, MAX_NAME_LEN, stdin);
  name[strcspn(name, "\n")] = 0;

  int i;
  for (i = 0; i < MAX_BOATS; i++) {
    if (boats[i] != NULL && strcasecmp(boats[i]->name, name) == 0) {
      float payment;
      printf("Please enter the amount to be paid: ");
      scanf("%f", &payment);

      if (payment > boats[i]->amountOwed) {
        printf("That is more than the amount owed, $%.2f\n", boats[i]->amountOwed);
        return;
      }

      boats[i]->amountOwed -= payment;
        return;
    }
  }
  printf("No boat with that name\n");
}

//--------------------------------------------------------------------------------------------------
//----Function to update the amount owed on the boat as if a month has passed
void updateCharges(Boat **boats) {
  float slipRate = 12.50;
  float landRate = 14.00;
  float trailorRate = 25.00;
  float storageRate = 11.20;

  int i;
  for (i = 0; i < numBoats; i++) {
    Boat *boat = boats[i];
    if (boat == NULL) {
      continue;
    }

    float length = boat->length;
    float rate;
    switch (boat->type) {
      case SLIP:
        rate = slipRate;
        break;
      case LAND:
        rate = landRate;
        break;
      case TRAILOR:
        rate = trailorRate;
        break;
      case STORAGE:
        rate = storageRate;
        break;
      default:
        rate = 0.0;
        break;
    }

    float amountOwed = length * rate;
    boat->amountOwed = boat->amountOwed + amountOwed;
  }
}

//--------------------------------------------------------------------------------------------------
//----Function to save the boats and all their information back into the original csv file
void saveInventory(char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("Error opening file\n");
    return;
  }
    
  for (int i = 0; i < numBoats; i++) {
    Boat *boat = boats[i];
    char typeStr[10];
    switch (boat->type) {
      case SLIP:
        strcpy(typeStr, "slip");
        break;
      case LAND:
        strcpy(typeStr, "land");
        break;
      case TRAILOR:
        strcpy(typeStr, "trailor");
        break;
      case STORAGE:
        strcpy(typeStr, "storage");
        break;
    }
    fprintf(fp, "%s,%d,%s,", boat->name, boat->length, typeStr);
    switch (boat->type) {
      case SLIP:
        fprintf(fp, "%d,", boat->location.slipNum);
        break;
      case LAND:
        fprintf(fp, "%c,", boat->location.bayLetter);
        break;
      case TRAILOR:
        fprintf(fp, "%s,", boat->location.trailorTag);
        break;
      case STORAGE:
        fprintf(fp, "%d,", boat->location.storageNum);
        break;
    }
      fprintf(fp, "%.2f\n", boat->amountOwed);
  }
    
  int close_result = fclose(fp);
  if(close_result == EOF) {
    printf("Error closing file\n");
  }
}

//--------------------------------------------------------------------------------------------------
//----Function to free the memory that was malloced for the boat array
void freeBoat(Boat *boat){
  free(boat);
}

//--------------------------------------------------------------------------------------------------
//----Main function to print the welcome and exit message
//----as well as to present the user with their menu choices
int main(int argc, char* argv[]) {

  if (argc != 2) {
    printf("Usage: %s <inventory_file>\n", argv[0]);
    return 1;
  }

  loadInventory(argv[1]);
  
  printf("\nWelcome to the Boat Management System");
  printf("-------------------------------------\n");

  char choice = '\0';
  while(choice != ('X' | 'x')) {
    printf("\n(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
    scanf(" %c", &choice);
    switch (choice) {
      case 'I':
      case 'i':
        printInventory(boats);
        break;
      case 'A':
      case 'a':
        addBoat();
        break;
      case 'R':
      case 'r':
        remove_boat();
        break;
      case 'P':
      case 'p':
        acceptPayment(boats);
        break;
      case 'M':
      case 'm':
        updateCharges(boats);
        break;
      case 'X':
      case 'x':
        break;
      default:
        printf("Invalid option %c\n", choice);
    }
  }
  saveInventory(argv[1]);

  for(int i = 0; i < numBoats; i++){
    if(boats[i] != NULL){
      freeBoat(boats[i]);
    }
  }

  printf("\nExiting the Boat Mangement System\n");
}

