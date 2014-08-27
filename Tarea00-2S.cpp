#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include "FECHACOMPILACION.h"   //para imprimir la fecha en formato ISO
using namespace std;

void error(int cod){
    if (cod==1)
        printf("\nDebe ingresar al menos un parametro...\n");
    else
        printf("\nParametros invalidos o inexistentes (Parametros: %d)\n", cod-1);
}



void informacion(){
    char fechayhora[80];
    time_t tiempo;
    struct tm *punterotm;
    tiempo = time(NULL);
    punterotm= localtime(&tiempo);
    strftime( fechayhora, 80, "%Y-%m-%d %X", punterotm);
    printf("Compilacion: %d-%02d-%02d %s", YEAR, MONTH +1, DAY, __TIME__);
    printf("\nFecha y hora actual: %s", fechayhora);
    printf("\nVersion 0.1.0");
    printf("\n\nIntegrantes: \n Alejandra Munoz\n Marcial Jara\n Henry Sepulveda\n");
}

void grafico(char *tienda){    //Argumento -g <tienda>
    printf("\ngrafico(%s)\n\n", tienda);
 }

int main(int argc, char** argv) {

    if (argc==2){
        if (strcmp(argv[1],"-v")==0)
            informacion();
        else
            error(argc);
        }
    if (argc==4){
        if (strcmp(argv[1],"-g")==0) 
            grafico(argv[2]);
        else
            error(argc);
    }
    if (argc==1 || argc>3){
        error(argc);
    }
    return 0;
}
