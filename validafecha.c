
#include <stdio.h>
#include <ctype.h>

int validarfecha(char* fecha){
	int error = 0;
	int i;
	for(i=0; i<4; i++)
            if (isdigit(fecha[i]))
                 error = 0;
            else
                error = 1;
	if ((isdigit(fecha[5])) && (isdigit(fecha[6])) && (isdigit(fecha[8])) && (isdigit(fecha[9])))
	        error = 0;
            else
                error = 1;
	if (fecha[10]!='\0'){
            error = 1;
        }
	if (error != 0)
		printf("\n\nError: formato de fecha inválido\nFormato esperado: yyyy-mm-dd\n");
	return error;
}