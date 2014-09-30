
#include <stdio.h> 
#include <stdlib.h> 


int main() { 
   char cadena[100]; 
   FILE *pf; 
   int i;
   pf = fopen("texto.txt","w"); 
   for (i = 1; i <= 3; i++){ 
      printf("Texto %d: ", i); 
      gets(cadena); 
      fprintf(pf," %snn",cadena); 
   } 
   fclose(pf); 

}