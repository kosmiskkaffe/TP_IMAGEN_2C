#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funciones_alvarez.h"


void negativo(t_pixel** imagen, int ancho, int alto)
{

    for (int i =0; i<alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            //printf("Antes: R=%d, G=%d, B=%d\n", imagen[i][j].pixel[0], imagen[i][j].pixel[1], imagen[i][j].pixel[2]);
            imagen[i][j].pixel[0] = 255 - imagen[i][j].pixel[0];
            imagen[i][j].pixel[1] = 255 - imagen[i][j].pixel[1];
            imagen[i][j].pixel[2] = 255 - imagen[i][j].pixel[2];
            //printf("Despues: R=%d, G=%d, B=%d\n", imagen[i][j].pixel[0], imagen[i][j].pixel[1], imagen[i][j].pixel[2]);
        }
    }

}

void escala_de_grises(t_pixel** imagen, int ancho, int alto)
{
    for (int i =0; i<alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            unsigned char promedio = (imagen[i][j].pixel[0]+imagen[i][j].pixel[1]+imagen[i][j].pixel[2])/3;
            imagen[i][j].pixel[0] = promedio;
            imagen[i][j].pixel[1] = promedio;
            imagen[i][j].pixel[2] = promedio;
        }
    }
}

void aumentar_contraste(t_pixel** imagen, int ancho, int alto, int nivel)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            t_pixel* pixel = &imagen[i][j];

            // Ajustar el contraste para cada componente del píxel
            for (int k = 0; k < 3; k++)
            {
                //Aumento el contraste en un 10% le paso nivel 10 y lo divido por 100 par tener 0.1
                int nuevo_valor = pixel->pixel[k] + (pixel->pixel[k] - 128) * nivel / 100;
                // Asegurarse de que los valores estén en el rango [0, 255]
                pixel->pixel[k] = nuevo_valor < 0 ? 0 : (nuevo_valor > 255 ? 255 : nuevo_valor);
            }
        }
    }
}

void reducir_contraste(t_pixel** imagen, int ancho, int alto, int nivel)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int nuevo_valor = imagen[i][j].pixel[k] - (imagen[i][j].pixel[k] - 128) * nivel/100;
                if (nuevo_valor < 0) nuevo_valor = 0;
                if (nuevo_valor > 255) nuevo_valor = 255;
                imagen[i][j].pixel[k] = nuevo_valor;
            }
        }
    }
}

void aumentar_azul(t_pixel** imagen, int ancho, int alto,int nivel)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            int nuevo_valor = imagen[i][j].pixel[0] + imagen[i][j].pixel[0] * nivel/ 100;
            if (nuevo_valor > 255) nuevo_valor = 255; // Me aseguro de que no exceda 255
            imagen[i][j].pixel[0] = nuevo_valor;
        }
    }
}










