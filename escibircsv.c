
#include <stdio.h> 
#include <stdlib.h> 
#include "libpq-fe.h"          //para conectar a BD PostgreSQL

int generarcsv(char* fecha_inicio, char* fecha_termino) { 
   char cadena[100]; 
   FILE *pf; 
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
            snprintf(sql, 512, "select count(peticion) as cant_pet, peticion FROM isw.accesos where fecha BETWEEN '%s 00:00:00' AND '%s 23:59:59' group by peticion ORDER BY cant_pet desc limit 100;", fecha_inicio, fecha_termino);
            res = PQexec(conn, sql);
                    
            printf(" Coneccion exitosa.\n");
            
            tuplas = PQntuples(res);
            pf = fopen("archivo.csv","w"); 
            //Copia el resultado de la consulta al archivo
            for (i=0; i<tuplas; i++) {         
                fprintf(pf,"\"%d\";\"%s\";\"%s\"\r\n",i+1,PQgetvalue(res,i,0),PQgetvalue(res,i,1)); 
             }
            printf("\nEl archivo csv ha sido guardado como archivo.csv en el directorio actual\n");
     }else
            printf("\nError: Ha ocurrido un problema en la coneccion\n");    

   fclose(pf); 

}