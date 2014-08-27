#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include "libpq-fe.h"          //para conectar a BD PostgreSQL
#include "FECHACOMPILACION.h"   //para imprimir la fecha en formato ISO
using namespace std;

void error(int cod){
    if (cod==1)
        printf("\nDebe ingresar al menos un parametro...\n");
    else
        printf("\nParametros invalidos o inexistentes (%d)\n", cod);
}

/* Código heredado de la tarea anterior:
 
signed long stringAint(char *cadena){
    int i;
    cadena[0]='0';
    i=strlen(cadena);
    cadena[i-3]='0';
    return((atoi(cadena))/10);
}
int numerodemes(char *fecha){
    char numero[2];
    numero[0]=fecha[6];
    numero[1]=fecha[7];
    return (atoi(numero));
}
void eliminarcomillas(char *nombre){
    int i,j;
    j=strlen(nombre);
    nombre[j-1]='\0'; //Borra comillas del final
    for(i=0;i<j;i++)
        nombre[i]=nombre[i+1];
}
void mesenplabras(int num,char *messtr){
    switch(num){
        case 0: strcpy(messtr,"Enero"); break;
        case 1: strcpy(messtr,"Febrero"); break;
        case 2: strcpy(messtr,"Marzo"); break;
        case 3: strcpy(messtr,"Abril"); break;
        case 4: strcpy(messtr,"Mayo"); break;
        case 5: strcpy(messtr,"Junio"); break;
        case 6: strcpy(messtr,"Julio"); break;
        case 7: strcpy(messtr,"Agosto"); break;
        case 8: strcpy(messtr,"Septiembre"); break;
        case 9: strcpy(messtr,"Octubre"); break;
        case 10: strcpy(messtr,"Noviembre"); break;
        case 11: strcpy(messtr,"Diciembre"); break;
        
    }
}
*/

void help(char *cad){    // Argumento -h
    printf("%s\n", cad);
    printf("\nArgumentos:\n");
    printf(" -bh                Retorna hora del dia en donde en promedio, se vende mas por cada una de las tiendas\n");
    printf(" -h                 Retorna informacion con la forma de uso del programa\n");
    printf(" -g <tienda>        Genera grafico de barras en formato JPG, del total de las ventas del año\n");
    printf(" -r                 Retorna la suma de las ventas por cada tienda\n");
    printf(" -v                 Acerca de Tarea3\n\n");
}

void suma_total_por_tienda(){       // Argumento -r
     
        printf("\n  *** Monto total de ventas por tienda *** \n");
        
        int i,j,k,len, tuplas, campos;   // tuplas=filas, campos=columanas 
        
        printf("\nConectando a servidor, por favor espere...");
        
        PGconn *conn = NULL; //Struct de estado de coneccion
        PGresult *res = NULL; //Puntero a tabla dinamica con los datos solic 
                              //de a la BD
        const char *host = "sebastian.cl"; //Las cadenas const char puede ser  
        const char *port = "5432";         //asinados con "=", las char no
        const char *dataBase = "iswdb";
        const char *user = "isw";
        const char *passwd = "isw";
       
        conn = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
        
        if (PQstatus(conn) != CONNECTION_BAD){       //Si la coneccion es exitosa...
            res = PQexec(conn,"select tienda, SUM(monto) FROM ventas group by tienda");
            printf(" Coneccion exitosa.\n");
            tuplas = PQntuples(res);
            campos = PQnfields(res);   // =>Columnas
            printf("\nVentas totales:\n");
            printf("\n  tienda   | monto ($)");
            printf("\n-----------+-----------\n");
            for (i=0; i<tuplas; i++) {
                for (j=0; j<campos; j++) {
                    printf(" %s ", PQgetvalue(res,i,j));
                    
                    
                    if (j==0){                               //No repetir linea vertical
                        len = 9-strlen(PQgetvalue(res,i,j));
                        for (k=1; k<=len; k++)               //Para imprimir correctamente  
                            printf(" ");                     //la tabla.
                        printf("|");                         //Line vertical de la tabla
                    }
                }
                printf("\n");
             }
             printf("\n");
        }else
            printf("\nError: Ha ocurrido un problema en la coneccion\n");
}

void hora_pick_por_tienda(){     //Argumento -bh
        printf("\nhora_pick_por_tienda()\n\n");
        printf("\n  *** Hora promedio donde más se vende *** \n");
        
        int i,j,tuplas, campos;   // tuplas=filas, campos=columanas 
        
        printf("\nConectando a servidor, por favor espere...");
        
        PGconn *conn = NULL; //Struct de estado de coneccion
        PGresult *res = NULL; //Puntero a tabla dinamica con los datos solic 
                              //de a la BD
        const char *host = "sebastian.cl"; //Las cadenas const char puede ser  
        const char *port = "5432";         //asinados con "=", las char no
        const char *dataBase = "iswdb";
        const char *user = "isw";
        const char *passwd = "isw";
       
        conn = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
        
        if (PQstatus(conn) != CONNECTION_BAD){       //Si la coneccion es exitosa...
            res = PQexec(conn,"select date_trunc('day',fecha), max(monto) from ventas where tienda='Replay' group by date_trunc('day',fecha) order by date_trunc('day', fecha)");
            printf(" Coneccion exitosa.\n");
            
            tuplas = PQntuples(res);
            campos = PQnfields(res);   // =>Columnas
            
            printf("el número de campos (columnas) es: %d\n", PQnfields(res));
            printf("el número de filas es: %d\n", PQntuples(res));
            
            printf("\nVentas totales:\n");
            printf("\n          fecha      |  monto ($)");
            printf("\n---------------------+-------------\n");
            for (i=0; i<tuplas; i++) {
                for (j=0; j<campos; j++) {
                    printf(" %s ", PQgetvalue(res,i,j));
                    if (j==0){                               //No repetir linea vertical
                      /*  len = 9-strlen(PQgetvalue(res,i,j));
                        for (k=1; k<=len; k++)               //Para imprimir correctamente  
                            printf(" ");                     //la tabla.
                       */printf("|");                         //Line vertical de la tabla
                    }
                }
                printf("\n");
             }
             printf("\n");
        }else
            printf("\nError: Ha ocurrido un problema en la coneccion\n");
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
    if (argc==1)
        help(argv[0]);
    if (argc==2){
        if (strcmp(argv[1],"-h")==0)
            help(argv[0]);
        if (strcmp(argv[1],"-r")==0)
            suma_total_por_tienda();
        if (strcmp(argv[1],"-bh")==0) //hora en que se registran más ventas en
            hora_pick_por_tienda();  // promedio por tienda
        if (strcmp(argv[1],"-v")==0)
            informacion();
        if ((strcmp(argv[1],"-h")!=0) && (strcmp(argv[1],"-r")!=0) && (strcmp(argv[1],"-bh")!=0) && (strcmp(argv[1],"-v")!=0))
            error(2);
    }
    if (argc==3){
        if (strcmp(argv[1],"-g")==0) 
            grafico(argv[2]);
        else
            error(3);
    }
    if (argc>3){
        error(argc);
    }
    return 0;
}
