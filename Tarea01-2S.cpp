#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include "FECHACOMPILACION.h"   //para imprimir la fecha en formato ISO
#include "libpq-fe.h"          //para conectar a BD PostgreSQL
#include "utils.h"
#include "graficador.c"
#include "graficadortorta.c"

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
    printf("Fecha de Compilaci\242n: %d-%02d-%02d %s", YEAR, MONTH +1, DAY, __TIME__);
    printf("\nFecha y hora actual: %s", fechayhora);
    printf("\nVersion 0.0.1");
    printf("\n\nIntegrantes: \n Alejandra Mu\xA4oz\n Henry Sep\243lveda\n");
}

void opciong(char *fecha_inicio, char *fecha_termino){ 

        long cantpetpormes[12]; //arreglo que almacena la cant de peticiones por mes
        int i,j,tuplas, campos;   // tuplas=filas, campos=columanas 
        
        printf("\nConectando a servidor...");
        
        PGconn *conn = NULL; //Struct de estado de coneccion
        PGresult *res = NULL; //Puntero a tabla dinamica con los datos solic 
                              //de a la BD
        const char *host = "146.83.181.4"; //Las cadenas const char puede ser  
        const char *port = "6432";         //asinados con "=", las char no
        const char *dataBase = "iswdb";
        const char *user = "estisw";
        const char *passwd = "estisw";
       
        conn = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
        
        if (PQstatus(conn) != CONNECTION_BAD){       //Si la coneccion es exitosa...
            res = PQexec(conn,"select EXTRACT(MONTH FROM fecha) AS mes, count(peticion) as cant_pet FROM isw.accesos where fecha BETWEEN '2014-03-01 00:00:00' AND '2014-11-30 23:59:59' group by mes ORDER BY mes;");
            printf(" Coneccion exitosa.\n");
            
            tuplas = PQntuples(res);
            campos = PQnfields(res);   // =>Columnas
            /*
            printf("el número de campos (columnas) es: %d\n", PQnfields(res));
            printf("el número de filas es: %d\n", PQntuples(res));
            
            printf("\nPeticiones:\n");
            printf("\n          mes        |  cantidad ($)");
            printf("\n---------------------+-------------\n");
            */
            //Se inicializa arreglo, valores menor a 0 equivalen a NULL en graficobarras()
            for (i=0; i<12; i++) 
                cantpetpormes[i] = -2;
            //Copia el resultado de la consulta al arreglo
            for (i=0; i<tuplas; i++) {         
                cantpetpormes[atoi(PQgetvalue(res,i,0))-1] = atol(PQgetvalue(res,i,1));
                /*for (j=0; j<campos; j++) {
                    printf(" %s ", PQgetvalue(res,i,j));
                    if (j==0){                         //No repetir linea vertical
                         printf("|");         //Linea vertical de la tabla
                    }
                }
                printf("\n"); */
             }
        }else
            printf("\nError: Ha ocurrido un problema en la coneccion\n");
        /*for (i=0; i<12; i++) 
                printf("\ncantpetpormes[%d]: %ld",i,cantpetpormes[i]);*/
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
