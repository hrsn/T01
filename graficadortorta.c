
#include "gd.h"
#include "gdfonts.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "grafico.h"
#include "utils.h"

#define PI 3.14159265

char* intStr(int num) {
    char* texto = NULL;
    texto = (char *) calloc(65, sizeof (char *));
    snprintf(texto, 32, "%d", num);
    return texto;
}

int color_aleatoreo2() {
    return rand() % 256;
}
void graficotorta(int n, long cantidad[], int estado[]) {

    gdImagePtr imagen;
    FILE *archivo;
    char titulo[513];
    char etiqueta[512];
    int blanco, negro, color;
    gdFontPtr fuente = gdFontGetSmall();
    
    imagen = gdImageCreateTrueColor(IMG_WIDTH, IMG_HEIGHT);

    int i;
    int angEtiqueta, xEtiqueta, yEtiqueta;
    float eqgrados;
    int iniciotrozo, fintrozo;
    long suma = 0;
    int aprox;
    for (i=0; i<n; i++) {    
        suma = suma + cantidad[i];
    }
    eqgrados = 360.0/suma;
    
    if (imagen) {
        blanco = gdImageColorAllocate(imagen, 255, 255, 255);
        negro = gdImageColorAllocate(imagen, 0, 0, 0);
        // Pintamos el fondo Blanco
        gdImageFill(imagen, 0, 0, blanco);
        iniciotrozo = 0;
        for (i=0; i<n; i++) {
            fintrozo = (int) iniciotrozo+cantidad[i]*eqgrados;
            angEtiqueta = (iniciotrozo + fintrozo) / 2;
            xEtiqueta = cos(angEtiqueta*PI/180) * 220 + 400;
            yEtiqueta = sin(angEtiqueta*PI/180) * 220 + 290;
            // Color
            color = gdImageColorAllocate(imagen, color_aleatoreo(), color_aleatoreo(), color_aleatoreo());
            //Pintamos fondo el trozo
            gdImageFilledArc(imagen, 400, 300, 400, 400, iniciotrozo, fintrozo, color, gdArc);       
            //Etiqueta de peticion
            memset(etiqueta, 0, 513);
            snprintf(etiqueta, 512, "peticion %s",intStr(estado[i]));
            gdImageString(imagen, fuente, xEtiqueta-25, yEtiqueta, (unsigned char *) etiqueta, negro);
            //Correccion de aproximacion para el porcentaje
            aprox = cantidad[i] * 1000 / suma;
            aprox = aprox%10;
            if (aprox>=5)
                aprox = 1;
            else
                aprox = 0;
            //Etiqueta de porcentaje
            memset(etiqueta, 0, 513);
            snprintf(etiqueta, 512, "%s%%",longStr(cantidad[i]*100/suma+aprox));
            if (cantidad[i]*100/suma<3){      //Para que la etiqueta sea legible
                xEtiqueta = xEtiqueta + 52;
                yEtiqueta = yEtiqueta - 15;
            }
            gdImageString(imagen, fuente, xEtiqueta, yEtiqueta+15, (unsigned char *) etiqueta, negro);
            iniciotrozo = (int) iniciotrozo+cantidad[i]*eqgrados;
        }

        //Pintamos borde del circulo
        gdImageArc(imagen, 400, 300, 400, 400, 0, 360, negro);
        // Coloco el título
        memset(titulo, 0, 513);
        snprintf(titulo, 512, "Peticiones Por Estado");
        gdImageString(imagen, fuente, (int) IMG_WIDTH * 0.4, 25, (unsigned char *) titulo, negro);
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