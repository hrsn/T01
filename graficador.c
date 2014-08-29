#include "gd.h"
#include "gdfonts.h"
#include <stdio.h>
#include <string.h>

int graficar(long long unsigned multitienda[]) {
	gdImagePtr img; //declaración de la imagen
	FILE *archivo; //archivo de salida
	int black,white;
        int xtexto=20;
        int ytexto=24;
        char palabra[513];
	img = gdImageCreate(170,100); //crea una imagen, 170 por 100 pixeles
        gdFontPtr fuente = gdFontGetSmall();
        
        //printf("\ngraficador\nCencosux: $ %llu \nFalaferia: $ %llu\nPorahi: $ %llu\nReplay: $ %llu\n",multitienda[0],multitienda[1],multitienda[2],multitienda[3]);
        
	black = gdImageColorAllocate(img, 0, 0, 0); //asignar color negro
	white = gdImageColorAllocate(img, 255, 255, 255);	//asignar color blanco
	gdImageFill(img, 0, 0, white);
        //gdImageLine(img, 0, 0,100,100, black); // dibuja una línea utilizando el color blanco.
        
        memset(palabra, 0, 513);
        snprintf(palabra, 512, "CencoSux: $%llu",multitienda[0]);
        gdImageString(img, fuente, xtexto, ytexto, (unsigned char *) palabra, black);
        
        ytexto=ytexto+12;   
        snprintf(palabra, 512, "Falaferia: $%llu",multitienda[1]);
        gdImageString(img, fuente, xtexto, ytexto, (unsigned char *) palabra, black);
        
        ytexto=ytexto+12;   
        snprintf(palabra, 512, "Porahi: $%llu",multitienda[2]);
        gdImageString(img, fuente, xtexto, ytexto, (unsigned char *) palabra, black);
        
        ytexto=ytexto+12;   
        snprintf(palabra, 512, "Replay: $%llu",multitienda[3]);        
        gdImageString(img, fuente, xtexto, ytexto, (unsigned char *) palabra, black);
	
        archivo = fopen("resultados.jpg", "wb"); //abre un archivo
	if (archivo != NULL) {
                gdImageJpeg(img, archivo, -1); //guarda la imagen en el archivo utilizando la calidad por default
                fclose(archivo); 
	}
        
        gdImageDestroy(img);
}