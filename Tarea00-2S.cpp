#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include "FECHACOMPILACION.h"   //para imprimir la fecha en formato ISO
#include "graficador.c"
using namespace std;

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
    //printf("Fecha de Compilacion: %s %s\n", __DATE__, __TIME__);
    printf("\nFecha y hora actual: %s", fechayhora);
    printf("\nVersi\242n 1.1.4");
    printf("\n\nIntegrantes: \n Alejandra Mu\xA4oz\n Henry Sep\243lveda\n");
}
void suma_ventas_rango(char *fecha_inicio, char *fecha_termino, char *archivocsv){ 
        char buffer[51];
        char *monto_string, *nombre, *fecha;
        unsigned long monto=0;
        unsigned long long multitienda[4]; //arreglo que almacena las ventas de por cadena
        int i;
        FILE *archivo;
        for (i=0;i<=3;i++)
              multitienda[i]=0; //inicializa valores en arreglo
        archivo=fopen(archivocsv, "r"); //abre para lectura ("r") - r/w
        if(archivo==NULL) //comprobaciÃ³n de apertura
                printf("\n el archivo no se pudo abrir\n");
        else
            printf("\nPara ver la suma de ventas totales por tienda revise el archivo resultados.jpg\n");
        while (feof(archivo)==0){
                fgets(buffer, 50, archivo);  //se toma una fila del archivo
                if (feof(archivo)==0){      //condicion necesaria para evitar punteros a vacÃ­os
                        nombre=strtok(buffer,";");  //Se separan los campos nombre, fecha, monto de venta en variables
                        fecha=strtok(NULL,";");
                        eliminarcomillas(fecha);   //Se eliminan las ""
                        monto_string=strtok(NULL,";");
                        eliminarcomillas(nombre);   //Se eliminan comillas 
                        if (yyyymmdd_toint(fecha)>=yyyymmdd_toint(fecha_inicio))
                            if (yyyymmdd_toint(fecha)<=yyyymmdd_toint(fecha_termino)){
                                monto=stringtoint(monto_string); //Se convierte la cadena monto en un entero 
                                if(strcmp("CencoSux",nombre)==0)  
                                        multitienda[0]=multitienda[0]+monto;
                                if(strcmp("Falaferia",nombre)==0)
                                        multitienda[1]=multitienda[1]+monto;   
                                if(strcmp("Porahi",nombre)==0)   
                                        multitienda[2]=multitienda[2]+monto;                               
                                if(strcmp("Replay",nombre)==0)   
                                        multitienda[3]=multitienda[3]+monto;   
                                }      
                }
        }
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
    if (argc==5){
        if (strcmp(argv[1],"-g")==0) 
            suma_ventas_rango(argv[2],argv[3],argv[4]);
        else
            error(argc);
    }
    if (argc<2 || argc==3 || argc==4 || argc>5){
        error(argc);
    }
    return 0;
}
