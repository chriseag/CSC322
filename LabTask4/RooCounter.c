//----Roo Roadkill Counter
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 0.01 //average Australian road width in km
#define ROADKILLCONST 1.47 //roadkill probability constant
//--------------------------------------------------------------------------------------------------
int main(void) {

  /*
   Function used to calculate the number of expected kangaroo roadkills each year.
   First finds kangaroo density, then finds the road surface area.
   These values are multipled by the roadkill probability constant.
  */

  //-----set all variables
  float squarelength;
  float roadlength;
  float deaths;
  float kangaroodensity;
  float roadsurfacearea;
  int kangaroos;

  //----take info from user
  printf("Enter side of square in km : ");
  scanf("%f", &squarelength);
  printf("Enter roads length in km : ");
  scanf("%f", &roadlength);
  printf("Enter number of 'roos : ");
  scanf("%d", &kangaroos);

  //----calculate kangaroo density
  kangaroodensity = (kangaroos / (squarelength * squarelength));
  //----calculate road surface area
  roadsurfacearea = (roadlength*WIDTH);
  //----calculate number of expected kangaroo roadkills per year
  deaths = (kangaroodensity * roadsurfacearea * ROADKILLCONST);

  //----print results	
  printf("Expected number of kills is : %.1f\n", deaths);
  
  //----exit program
  return (EXIT_SUCCESS);
}

	


