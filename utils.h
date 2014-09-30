/* 
 * File:   utils.h
 * Author: Sebastián Salazar Molina <sebasalazar@gmail.com>
 *
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

    void limpiar(void);
    void pausa(void);
    char* getString(char *texto);
    long getLong(char *texto);
    int getInt(char *texto);
    double getDouble(char *texto);
    char* leer_string(char *label);
    long leer_long(char *label);
    int leer_int(char *label);
    char* ahora();
    int color_aleatoreo();
    char* etiquetaMes(int num);
    char* longStr(long num);
#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

