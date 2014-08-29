#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include "FECHACOMPILACION.h"   //para imprimir la fecha en formato ISO
//#include "gd.h"
//#include "gdfonts.h"
#include "graficador.c"
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
    printf("Fecha de Compilacion: %d-%02d-%02d %s", YEAR, MONTH +1, DAY, __TIME__);
    //printf("Fecha de Compilacion: %s %s\n", __DATE__, __TIME__);
    printf("\nFecha y hora actual: %s", fechayhora);
    printf("\nVersion 1.0.2");
    printf("\n\nIntegrantes: \n Alejandra Munoz\n Henry Sepulveda\n");
}
signed long stringAint(char *cadena){
    int i;
    cadena[0]='0';
    i=strlen(cadena);
    cadena[i-3]='0';
    return(atoi(cadena));
}
void eliminarcomillas(char *nombre){
    int i,j;
    j=strlen(nombre);
    nombre[j-1]='\0'; //Borra comillas del final
    for(i=0;i<j;i++)
        nombre[i]=nombre[i+1];
}
void suma_de_ventas(char *archivocsv){
        char buffer[51];
        char *monto_string, *nombre, *fecha;
        unsigned long monto=0;
        unsigned long long multitienda[4];
        int i;
        FILE *archivo;
      
        for (i=0;i<=3;i++)
              multitienda[i]=0;

        archivo=fopen(archivocsv, "r"); //abre para lectura ("r") - r/w
        if(archivo==NULL) //comprobaciÃ³n de apertura
                printf("\n el archivo no se pudo abrir\n");
        else
            printf("\nPara ver la suma de ventas totales por tienda revise resultados.jpg\n");
        while (feof(archivo)==0){
                fgets(buffer, 50, archivo);  //se toma una fila del archivo
                if (feof(archivo)==0){      //condicion necesaria para evitar punteros a vacÃ­os
                        nombre=strtok(buffer,";");  //Se separan los campos nombre, fecha, monto de venta
                        fecha=strtok(NULL,";");
                        monto_string=strtok(NULL,";");
                        eliminarcomillas(nombre);   //Se eliminan comillas 
                        monto=stringAint(monto_string); //Se convierte la cadena monto en un entero 
             
                        if(strcmp("CencoSux",nombre)==0){   
                            multitienda[0]=multitienda[0]+monto;
                        }
                        if(strcmp("Falaferia",nombre)==0){   
                            multitienda[1]=multitienda[1]+monto;   
                        }
                          if(strcmp("Porahi",nombre)==0){   
                            multitienda[2]=multitienda[2]+monto;
                        }
                        if(strcmp("Replay",nombre)==0){   
                            multitienda[3]=multitienda[3]+monto;   
                        }
                        
                }
        }
       // printf("\nCencosux: $ %llu \nFalaferia: $ %llu\nPorahi: $ %llu\nReplay: $ %llu\n",multitienda[0],multitienda[1],multitienda[2],multitienda[3]);
        graficar(multitienda);
        fclose(archivo);     
}

int main(int argc, char** argv) {
    if (argc==2){
        if (strcmp(argv[1],"-v")==0)
            informacion();
        else
            error(argc);
        }
    if (argc==3){
        if (strcmp(argv[1],"-g")==0) 
            suma_de_ventas(argv[2]);
        else
            error(argc);
    }
    if (argc<=1 || argc>3){
        error(argc);
    }
    return 0;
}
