//----Allies
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------------------------

//----Typedef to create the nodes of the linked list
typedef struct node {
  char* country;
  char* best_ally;
  struct node* next;
  } Node;


//----Main function to run the entire program
int main(void) {
  //----Declares pointer to head node and current node
  //----Also creates a char array with length 100
  Node* head = NULL;
  Node* current = NULL;
  char input[100];

  //----Prompts user to input countries of interest, terminated by a blank entry
  while (1) {
    printf("Enter nation name : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    //----Stop asking for input if the user enters a blank line
    if (strlen(input) == 0) {
      break;
    }

    //----Create a new node for the country and add it to the linked list
    Node* new_node = malloc(sizeof(Node));
    new_node->country = malloc(strlen(input) + 1);
    strcpy(new_node->country, input);
    new_node->best_ally = NULL;
    new_node->next = NULL;

    if(head == NULL) {
      head = new_node;
      current = head;
    } 
    else {
      current->next = new_node;
      current = new_node;
    }
  }

  //----Prompt the user to enter the best ally for each country
  current = head;
  while (current != NULL) {
    printf("Enter best ally name for %s : ", current->country);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    //----Set best ally
    Node* best_ally_node = head;
    while (best_ally_node != NULL) {
      if (strcmp(best_ally_node->country, input) == 0) {
        current->best_ally = best_ally_node->country;
        break;
      }
      best_ally_node = best_ally_node->next;
    }
    current = current->next;
  }

  //----Print out best ally for each country
  current = head;
  while (current != NULL) {
    printf("The best ally of %s is %s\n", current->country, current->best_ally);
    current = current->next;
  }

  //----Free memory
  current = head;
  while (current != NULL) {
    Node* next_node = current->next;
    free(current->country);
    free(current);
    current = next_node;
  }
  return (EXIT_SUCCESS);
}
