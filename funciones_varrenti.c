#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funciones_varrenti.h"


void aumentar_verde(t_pixel** imagen, int ancho, int alto,int nivel)
{

    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {

            int nuevo_valor = imagen[i][j].pixel[1] + imagen[i][j].pixel[1] * nivel/ 100;
            if (nuevo_valor > 255) nuevo_valor = 255; // Me aseguro de que no exceda 255
            imagen[i][j].pixel[1] = nuevo_valor;
        }
    }
}

void espejar_horizontal(t_pixel** imagen, int ancho, int alto)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho / 2; j++)
        {
            // Intercambio los píxeles en la posición j y (ancho - j - 1)
            t_pixel temp = imagen[i][j];
            imagen[i][j] = imagen[i][ancho - j - 1];
            imagen[i][ancho - j - 1] = temp;
        }
    }
}



void recortar_30(t_pixel*** imagen, int* ancho, int* alto, t_metadata* metadata,int nivel)
{
    // Si recortamos la imagen en un 30%, quiere decir que nos quedamos con un 70% de la imagen?
    int nuevo_ancho = *ancho * (100 - nivel)/100;
    int nuevo_alto = *alto * (100 - nivel)/100;

    // Centro la imagen en 0,0

    int offset_x = (*ancho - nuevo_ancho) / 2;
    int offset_y = (*alto - nuevo_alto) / 2;

    t_pixel** nueva_imagen = (t_pixel**)malloc(nuevo_alto * sizeof(t_pixel*));
    for (int i = 0; i < nuevo_alto; i++)
    {
        nueva_imagen[i] = (t_pixel*)malloc(nuevo_ancho * sizeof(t_pixel));
        for (int j = 0; j < nuevo_ancho; j++)
        {
            nueva_imagen[i][j] = (*imagen)[i + offset_y][j + offset_x];
        }
    }

    // Libero la memoria de la imagen original
    for (int i = 0; i < *alto; i++)
    {
        free((*imagen)[i]);
    }
    free(*imagen);

    // Actualizo los punteros y dimensiones
    *imagen = nueva_imagen;
    *ancho = nuevo_ancho;
    *alto = nuevo_alto;

    metadata->ancho = nuevo_ancho;
    metadata->alto = nuevo_alto;
}

void achicar_10(t_pixel*** imagen, int* ancho, int* alto,t_metadata* metadata,int nivel)
{
    // Si vos lo achicas en un 10%, quiere decir que la imagen debería mostrarse en un 90%
    int nuevo_ancho = *ancho * (100 - nivel)/100;
    int nuevo_alto = *alto * (100 - nivel)/100;

    // Creo una nueva imagen con el tamaño reducido
    t_pixel** nueva_imagen = (t_pixel**)malloc(nuevo_alto * sizeof(t_pixel*));
    if (nueva_imagen == NULL)
    {
        perror("Error al asignar memoria para nueva_imagen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nuevo_alto; i++)
    {
        nueva_imagen[i] = (t_pixel*)malloc(nuevo_ancho * sizeof(t_pixel));
        if (nueva_imagen[i] == NULL)
        {
            perror("Error al asignar memoria para nueva_imagen[i]");
            exit(EXIT_FAILURE);
        }
    }

    // Copio los píxeles de la imagen original a la nueva imagen
    for (int i = 0; i < nuevo_alto; i++)
    {
        for (int j = 0; j < nuevo_ancho; j++)
        {
            nueva_imagen[i][j] = (*imagen)[i][j];
        }
    }

    // Libero la memoria de la imagen original
    for (int i = 0; i < *alto; i++)
    {
        free((*imagen)[i]);
    }
    free(*imagen);

    // Asigno la nueva imagen a la imagen original
    *imagen = nueva_imagen;

    // Actualizo las dimensiones
    *ancho = nuevo_ancho;
    *alto = nuevo_alto;

    metadata->ancho = nuevo_ancho;
    metadata->alto = nuevo_alto;
}

void comodin_aplicar_desenfoque(t_pixel*** imagen, int ancho, int alto)
{
    t_pixel** nueva_imagen = (t_pixel**)malloc(alto * sizeof(t_pixel*));
    if (nueva_imagen == NULL)
    {
        perror("Error al asignar memoria para nueva_imagen");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < alto; i++)
    {
        nueva_imagen[i] = (t_pixel*)malloc(ancho * sizeof(t_pixel));
        if (nueva_imagen[i] == NULL)
        {
            perror("Error al asignar memoria para nueva_imagen[i]");
            exit(EXIT_FAILURE);
        }
    }

    // Aplicamos el filtro de desenfoque
    for (int i = 1; i < alto - 1; i++)
    {
        for (int j = 1; j < ancho - 1; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                nueva_imagen[i][j].pixel[k] = (
                                                  (*imagen)[i-1][j-1].pixel[k] + (*imagen)[i-1][j].pixel[k] + (*imagen)[i-1][j+1].pixel[k] +
                                                  (*imagen)[i][j-1].pixel[k] + (*imagen)[i][j].pixel[k] + (*imagen)[i][j+1].pixel[k] +
                                                  (*imagen)[i+1][j-1].pixel[k] + (*imagen)[i+1][j].pixel[k] + (*imagen)[i+1][j+1].pixel[k]
                                              ) / 9;
            }
        }
    }

    // Liberamos la memoria de la imagen original
    for (int i = 0; i < alto; i++)
    {
        free((*imagen)[i]);
    }
    free(*imagen);

    // Asignamos la nueva imagen a la imagen original
    *imagen = nueva_imagen;
}

