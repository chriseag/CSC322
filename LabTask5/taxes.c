//----Taxes
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------------------------

 /*
 This function computes the taxable income (income-deductions) and
 sets taxable income to 0 if deductions are greater than income
 */

float computetaxableincome(float income, float deduction){
  float taxableincome;
  if(income >= deduction){
    taxableincome = income-deduction;
  }
  else{
    taxableincome = 0;
  }
  return taxableincome;
}

 //This function computes the tax group based on income

char computetaxgroup(float taxableincome){
  char taxgroup;
  if(taxableincome >= 500000){
    taxgroup = 'S';
  }
  else if(taxableincome >= 200000){
    taxgroup = 'Q';
  }
  else if(taxableincome >= 100000){
    taxgroup = 'M';
  }
  else if(taxableincome >= 50000){
    taxgroup = 'A';
  }
  else if(taxableincome >= 20000){
    taxgroup = 'R';
  }
  else{
    taxgroup = 'P';
  }
  return taxgroup;
}

  /*
  This function computes tax based on which tax group the user 
  is in and how much their taxable income is. If this calculation
  results in tax over $50000 the tax is set to $50000.
  */

float computetax(float taxableincome, char taxgroup){
  float tax = 0.0;
  switch(taxgroup){
    case 'S':
    case 'Q':
      tax=0.25*taxableincome;
      break;
    case 'M':
      tax=0.10*taxableincome;
      break;
    case 'A':
    case 'R':
      tax=0.03*taxableincome;
      break;
    case 'P':
      tax=0.0;
      break;
    default:
      printf("Error!");
      break;
  }

  if(tax>50000){
    tax=50000.0;
  }
  
  return tax;
}
 
  /*
  The main method initializes all the variables, takes input
  from the user to find out thier income and deductions,
  runs all of the other functions and stores any information
  they return in a variable, and then prints out the results
  of the calculations. 
  */

int main(void) {

  float income;
  float deduction;
  float taxableincome;
  char taxgroup;
  int input;
  float tax;
  
  while(1){

    printf("Enter next amount : ");
    scanf("%d", &input);
    if(input == 0){
      break;
    }
    else if(input>0){
      income += input;
    }
    else if(input<0){
      deduction += -1*input;
    }
  }

  taxableincome = computetaxableincome(income, deduction);
  taxgroup = computetaxgroup(taxableincome);
  tax = computetax(taxableincome, taxgroup);

  printf("Income = $%.2f\n", income);
  printf("Deductions = $%.2f\n", deduction);
  printf("Taxable Income = $%.2f\n", taxableincome);
  printf("Tax group = %c\n", taxgroup);
  printf("Tax owed = $%.2f\n", tax);

  //----exit program
  return (EXIT_SUCCESS);


}



