
#include "gd.h"
#include "gdfonts.h"
#include <stdio.h>
#include <string.h>
#include "grafico.h"
#include "utils.h"

/*
 IMG_HEIGHT: 600
IMG_WIDTH: 800
BORDE_ALTO: 50
BORDE_ANCHO: 70

 */

void graficotorta(long peticiones[]) {
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
        //Pintamos fondo del circulo
        gdImageFilledArc(imagen, 400, 300, 400, 400, 0, 250, color_aleatoreo(), gdArc);
        //Pintamos borde del circulo
        gdImageArc(imagen, 400, 300, 400, 400, 0, 360, negro);
        
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

     /*  for (mes = 0; mes < 12; mes++) {
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
                gdImageString(imagen, fuente, ancho, IMG_HEIGHT - (BORDE_ALTO + alto + 20), (unsigned char *) longStr(peticiones[mes]), negro);
                ancho += 55;
           }else
                encoger++;
       }
      */ 
    
        // Pintamos Borde
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, negro); //linea horiz superior
        gdImageLine(imagen, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro); //linea horiz inferior
        gdImageLine(imagen, BORDE_ANCHO, BORDE_ALTO, BORDE_ANCHO, (IMG_HEIGHT - BORDE_ALTO), negro); //linea vertical izquierda
        gdImageLine(imagen, (IMG_WIDTH - BORDE_ANCHO), BORDE_ALTO, (IMG_WIDTH - BORDE_ANCHO), (IMG_HEIGHT - BORDE_ALTO), negro); //linea horiz derecha

        // Guardar imagen
        archivo = fopen("graficot.jpg", "wb");
        if (archivo != NULL) {
            gdImageJpeg(imagen, archivo, 100);
            fclose(archivo);
        }
        gdImageDestroy(imagen);
    }
 
}