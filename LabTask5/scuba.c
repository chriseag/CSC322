//----Scuba Dive Calculations
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ATMOSPHERECONST 33 //Feet per atmosphere constant
#define RECPARTIALPRESSURE 1.4 //recommended maximal partial pressure of oxygen
#define CONTPARTIALPRESSURE 1.6 //contingency maximal parital pressure of oxygen
//--------------------------------------------------------------------------------------------------
int main(void) {

  /*
	Function used to calculate Ambient pressure, O2 pressure, and O2 group.
        The function also checks whether or not the O2 pressure exceeds the maximal partial pressure
        of oxygen or the contingency maximal partial pressure of oxygen.
  */

  //-----set all variables
  int depth;
  float oxygenpercentage;
  float ambientpressure;
  float partialpressure;
  char oxygenpressuregroup = 'A';
  float looppartialpressure;
  bool recmax;
  bool contmax;  

  //----take info from user
  printf("Enter depth and percentage O2 : ");
  scanf("%d %f", &depth, &oxygenpercentage);


  //----calculate ambient pressure for the dive
  ambientpressure = (depth / ATMOSPHERECONST + 1);

  //----calculate partial pressure of oxygen for the dive
  partialpressure = (oxygenpercentage / 100 * ambientpressure);
  
  //----calculate oxygen pressure group
  looppartialpressure = partialpressure;
  while (looppartialpressure >= 0.1) {
        oxygenpressuregroup++;
        looppartialpressure -= 0.1;
    }

  //----check if dive will exceed maximal values
  recmax = partialpressure > RECPARTIALPRESSURE;
  contmax = partialpressure > CONTPARTIALPRESSURE;

  //----print results
  printf("Ambient pressure : %.1f\n", ambientpressure);
  printf("O2 pressure : %.2f\n", partialpressure);
  printf("O2 group : %c\n", oxygenpressuregroup);
  printf("Exceeds maiximal O2 pressure : %s\n", recmax ? "true" : "false");
  printf("Exceeds contingency O2 pressure : %s\n", contmax ? "true" : "false");

  //----exit program
  return (EXIT_SUCCESS);
}

