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
        char sql[513];
        
        printf("\nConectando a servidor...");
        
        PGconn *conn = NULL; //Struct de estado de coneccion
        PGresult *res = NULL; //Puntero a tabla dinamica con los datos solic de la BD
                              
        const char *host = "146.83.181.4";  //Las cadenas const char puede ser  
        const char *port = "6432";         //asinados con "=", las char no
        const char *dataBase = "iswdb";
        const char *user = "estisw";
        const char *passwd = "estisw";
       
        conn = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
        
        if (PQstatus(conn) != CONNECTION_BAD){       //Si la coneccion es exitosa...
            memset(sql, 0, sizeof (sql));
            snprintf(sql, 512, "select EXTRACT(MONTH FROM fecha) AS mes, count(peticion) as cant_pet FROM isw.accesos where fecha BETWEEN '%s 00:00:00' AND '%s 23:59:59' group by mes ORDER BY mes;", fecha_inicio,fecha_termino);
            res = PQexec(conn, sql);
                    
            printf(" Coneccion exitosa.\n");
            
            tuplas = PQntuples(res);
            campos = PQnfields(res);   // =>Columnas
            
            //Se inicializa arreglo, valores menor a 0 equivalen a NULL en graficobarras()
            for (i=0; i<12; i++) 
                cantpetpormes[i] = -2;
            //Copia el resultado de la consulta al arreglo
            for (i=0; i<tuplas; i++) {         
                cantpetpormes[atoi(PQgetvalue(res,i,0))-1] = atol(PQgetvalue(res,i,1));
                
                for (j=0; j<campos; j++) {
                    printf(" %s ", PQgetvalue(res,i,j));
                    if (j==0){                         //No repetir linea vertical
                         printf("|");         //Linea vertical de la tabla
                    }
                }
                printf("\n"); 
                
             }
            graficobarras(cantpetpormes); 
            printf("\nEl grafico de barras ha sido guardado como grafico.jpg en el directorio actual\n");
        }else
            printf("\nError: Ha ocurrido un problema en la coneccion\n");
    
}

void opciont(char *fecha_inicio, char *fecha_termino){ 

        long petporestado[100]; //arreglo que almacena la cant de peticiones por mes
        int estado[100];
        int i,j,tuplas, campos;   // tuplas=filas, campos=columanas 
        char sql[513];
        
        printf("\nConectando a servidor...");
        
        PGconn *conn = NULL; //Struct de estado de coneccion
        PGresult *res = NULL; //Puntero a tabla dinamica con los datos solic de la BD
                              
        const char *host = "146.83.181.4";  //Las cadenas const char puede ser  
        const char *port = "6432";         //asinados con "=", las char no
        const char *dataBase = "iswdb";
        const char *user = "estisw";
        const char *passwd = "estisw";
       
        conn = PQsetdbLogin(host, port, NULL, NULL, dataBase, user, passwd);
        
        if (PQstatus(conn) != CONNECTION_BAD){       //Si la coneccion es exitosa...
            memset(sql, 0, sizeof (sql));
            snprintf(sql, 512, "select count(peticion) as cant_pet, estado FROM isw.accesos where fecha BETWEEN '%s 00:00:00' AND '%s 23:59:59'group by estado ORDER BY cant_pet limit 5;", fecha_inicio, fecha_termino);
            res = PQexec(conn, sql);
                    
            printf(" Coneccion exitosa.\n");
            
            tuplas = PQntuples(res);
            campos = PQnfields(res);   // =>Columnas
      
            //Copia el resultado de la consulta a los arreglos
            for (i=0; i<tuplas; i++) {         
                petporestado[i] = atol(PQgetvalue(res,i,0));
                estado[i] = atoi(PQgetvalue(res,i,1));   
             }
            
            graficotorta(tuplas, petporestado, estado); 
            printf("\nEl grafico de torta ha sido guardado como graficot.jpg en el directorio actual\n");
        }else
            printf("\nError: Ha ocurrido un problema en la coneccion\n");    
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
