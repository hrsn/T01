#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include "FECHACOMPILACION.h"   //para imprimir la fecha en formato ISO
#include "utils.h"
#include "graficador.c"
#include "graficadortorta.c"

using namespace std;

/*
signed long stringtoint(char *cadena){
    int i;
    cadena[0]='0';
    i=strlen(cadena);
    cadena[i-3]='0';
    return(atoi(cadena));
}
int yyyymmdd_toint(char *fecha){
    char numero[2];
    numero[0]=fecha[0];
    numero[1]=fecha[1];
    numero[2]=fecha[2];
    numero[3]=fecha[3];
    numero[4]=fecha[5]; 
    numero[5]=fecha[6];
    numero[6]=fecha[8]; 
    numero[7]=fecha[9];
    return (atoi(numero));
}
void eliminarcomillas(char *nombre){
    int i,j;
    j=strlen(nombre);
    nombre[j-1]='\0'; //Borra las comillas del final
    for(i=0;i<j;i++)
        nombre[i]=nombre[i+1];
}
*/

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
    printf("Fecha de Compilaci\242n: %d-%02d-%02d %s", YEAR, MONTH +1, DAY, __TIME__);
    printf("\nFecha y hora actual: %s", fechayhora);
    printf("\nVersi\242n 0.0.0");
    printf("\n\nIntegrantes: \n Alejandra Mu\xA4oz\n Henry Sep\243lveda\n");
}

void opciong(char *fecha_inicio, char *fecha_termino){ 
        int i;
        long cantpetpormes[12]; //arreglo que almacena la cant de peticiones por mes
        for (i = 0; i < 6; i++){   //rellenando con datos solo para probar grafico
            cantpetpormes[i] = 1000;
        }
        for (i = 6; i < 12; i++){   //rellenando con datos solo para probar grafico
            cantpetpormes[i] = 1500;
        }
        cantpetpormes[0] = -12;  //rellenando con datos solo para probar grafico
        cantpetpormes[1] = -12;  //rellenando con datos solo para probar grafico
        cantpetpormes[11] = -12; //rellenando con datos solo para probar grafico
        graficobarras(cantpetpormes);  
}
void opciont(char *fecha_inicio, char *fecha_termino){ 
        int i;
        long cantpetpormes[12]; //arreglo que almacena la cant de peticiones por mes
        for (i = 0; i < 6; i++){   //rellenando con datos solo para probar grafico
            cantpetpormes[i] = 1000;
        }
        for (i = 6; i < 12; i++){   //rellenando con datos solo para probar grafico
            cantpetpormes[i] = 1500;
        }
        cantpetpormes[0] = -12;  //rellenando con datos solo para probar grafico
        cantpetpormes[1] = -12;  //rellenando con datos solo para probar grafico
        cantpetpormes[11] = -12; //rellenando con datos solo para probar grafico
        graficotorta(cantpetpormes);  
}
int main(int argc, char** argv) {
    if (argc==4){
        if (strcmp(argv[1],"-g")==0)
            opciong(argv[2],argv[3]); // Grafico de barras
        else
        if (strcmp(argv[1],"-t")==0) 
            opciont(argv[2],argv[3]); // Grafico de torta
        else
        if (strcmp(argv[1],"-a")==0) 
            opciong(argv[2],argv[3]); // Archivo csv
        else
            error(argc);
    }
    if (argc==2){
        if (strcmp(argv[1],"-v")==0)
            informacion();
        else
            error(argc);
        }
    
    if (argc<2 || argc==3 || argc>4){
        error(argc);
    }
    return 0;
}
