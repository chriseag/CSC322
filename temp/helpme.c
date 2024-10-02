#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <math.h>

int Spagbog(int Strands, jmp_buf Environment) {

if(Strands % 2) {
return (Strands / 2);
}
else{
longjmp(Environment,Strands / 4);
return(Strands / 8);
}
}

int main(int argc, char *argv[]){

int FoxyFiend;
jmp_buf Environment;

if((FoxyFiend = setjmp(Environment)) == 0){
printf("A: %d\n", FoxyFiend);
FoxyFiend = Spagbog(16, Environment);
printf("B: %d\n", FoxyFiend);
}
else{
printf("C: %d\n", FoxyFiend);
FoxyFiend = Spagbog(27, Environment);
printf("D: %d\n", FoxyFiend);
}
}
