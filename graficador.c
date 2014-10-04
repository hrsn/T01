#include "gd.h"
#include "gdfonts.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "grafico.h"
#include "utils.h"

char* etiquetaMes(int num) {
    char* etiqueta = NULL;
    etiqueta = (char *) calloc(5, sizeof (char *));
    num++;
    if (num == 1) {
        snprintf(etiqueta, 4, "Ene");
    }else if (num == 2) {
        snprintf(etiqueta, 4, "Feb");
    } else if (num == 3) {
        snprintf(etiqueta, 4, "Mar");
    } else if (num == 4) {
        snprintf(etiqueta, 4, "Abr");
    } else if (num == 5) {
        snprintf(etiqueta, 4, "May");
    } else if (num == 6) {
       snprintf(etiqueta, 4, "Jun");
    } else if (num == 7) {
        snprintf(etiqueta, 4, "Jul");
    } else if (num == 8) {
        snprintf(etiqueta, 4, "Ago");
    } else if (num == 9) {
        snprintf(etiqueta, 4, "Sep");
    } else if (num == 10) {
        snprintf(etiqueta, 4, "Oct");
    } else if (num == 11) {
        snprintf(etiqueta, 4, "Nov");
    } else if (num == 12) {
        snprintf(etiqueta, 4, "Dic");
    } else {
        snprintf(etiqueta, 1, " ");
    }
    return etiqueta;
}

char* longStr(long num) {
    char* texto = NULL;
    // Esto se puede hacer mejor, pero no hace daño
    texto = (char *) calloc(65, sizeof (char *));
    snprintf(texto, 64, "%ld", num);
    return texto;
}
int color_aleatoreo() {
    return rand() % 256;
}

void graficobarras(long peticiones[]) {
    //int color_aleatoreo();
    gdImagePtr imagen;
    FILE *archivo;
    char titulo[513];
    int blanco, negro, color;
    gdFontPtr fuente = gdFontGetSmall();
    
    imagen = gdImageCreateTrueColor(IMG_WIDTH, IMG_HEIGHT);

    int y = 0;
    int mes = 0;
    int alto = 50;
    int ancho = 70;
    int encoger = 0;
    long maximo = 0;
    long paso = 0;
    double porcentaje = 0.0;
    
    if (imagen) {
        blanco = gdImageColorAllocate(imagen, 255, 255, 255);
        negro = gdImageColorAllocate(imagen, 0, 0, 0);


        // Pintamos el fondo Blanco
        gdImageFill(imagen, 0, 0, blanco);
        // Buscamos el máximo
        for (mes = 0; mes < 12; mes++) {
            // Busco el valor máximo, este me permitira calcular cuanto es el alto máximo
            if (peticiones[mes] >= maximo) {
                maximo = peticiones[mes];
            }
        }
        maximo = maximo + (maximo/10); //Las etiquetas del costado llegan al 110% del maximo
 
        // Coloco la etiqueta al costado del gráfico
       for (y = BORDE_ALTO; y <= (BORDE_ALTO + 500); y = y + 50) {
            // Etiqueta
            gdImageString(imagen, fuente, 30, IMG_HEIGHT - y, (unsigned char *) longStr(paso), negro);
            paso += (maximo / 10);  //El maximo retoma su valor real
        }
       maximo = (maximo/11)*10;
       //printf("\nIMG_HEIGHT: %d",IMG_HEIGHT);
       //printf("\nBORDE_ALTO: %d",BORDE_ALTO);
       
       for (mes = 0; mes < 12; mes++) {
           if (peticiones[mes]>=0){
                // Color
                color = gdImageColorAllocate(imagen, color_aleatoreo(), color_aleatoreo(), color_aleatoreo());
                porcentaje = ((double) peticiones[mes] / maximo);
                // El alto máximo serán 500px que será el 100%
                alto = (int) (450 * porcentaje);
                // Barra
                gdImageFilledRectangle(imagen, ancho, IMG_HEIGHT - BORDE_ALTO, ancho + 40, IMG_HEIGHT - (BORDE_ALTO + alto), color);
                // Borde Negro
                gdImageRectangle(imagen, ancho, IMG_HEIGHT - BORDE_ALTO, ancho + 40, IMG_HEIGHT - (BORDE_ALTO + alto), negro);
                // Etiqueta del Mes  
                gdImageString(imagen, fuente, ancho + 15, IMG_HEIGHT - BORDE_ALTO + 5, (unsigned char *) etiquetaMes(mes), negro);
                // Monto
                gdImageString(imagen, fuente, ancho + 4, IMG_HEIGHT - (BORDE_ALTO + alto + 20), (unsigned char *) longStr(peticiones[mes]), negro);
                ancho += 55;
           }else
                encoger++;
       }
       // Coloco el título
        memset(titulo, 0, 513);
        snprintf(titulo, 512, "Peticiones Por Mes");
        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.4-encoger*26, 25, (unsigned char *) titulo, negro);
        // Pintamos Borde
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO)-encoger*55, BORDE_ALTO, negro); //linea horiz superior
        gdImageLine(imagen, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), (IMG_WIDTH - BORDE_ANCHO)-encoger*55, (IMG_HEIGHT - BORDE_ALTO), negro); //linea horiz inferior
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), negro); //linea vertical izquierda
        gdImageLine(imagen, (IMG_WIDTH - BORDE_ANCHO)-encoger*55, BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO)-encoger*55, (IMG_HEIGHT - BORDE_ALTO), negro); //linea horiz derecha

        // Guardar imagen
        archivo = fopen("grafico.jpg", "wb");
        if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
        }
        gdImageDestroy(imagen);
    }
 
}