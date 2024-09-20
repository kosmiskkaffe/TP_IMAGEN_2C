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

void recortar_30(t_pixel** imagen, int ancho, int alto)
{
    int nuevo_ancho = ancho * 0.3;
    int nuevo_alto = alto * 0.3;

    t_pixel** nueva_imagen = (t_pixel**)malloc(nuevo_alto * sizeof(t_pixel*));
    for (int i = 0; i < nuevo_alto; i++)
    {
        nueva_imagen[i] = (t_pixel*)malloc(nuevo_ancho * sizeof(t_pixel));
    }

    for (int i = 0; i < nuevo_alto; i++)
    {
        for (int j = 0; j < nuevo_ancho; j++)
        {
            nueva_imagen[i][j] = imagen[i][j];
        }
    }

    // Libero la memoria de la imagen original si ya no se necesita
    for (int i = 0; i < alto; i++)
    {
        free(imagen[i]);
    }
    free(imagen);

    // Asigno la nueva imagen a la imagen original
    imagen = nueva_imagen;
}

void achicar_10(t_pixel*** imagen, int* ancho, int* alto)
{
    int nuevo_ancho = *ancho * 0.9;
    int nuevo_alto = *alto * 0.9;

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
}

void concatenar_vertical(t_pixel*** imagen1, int ancho1, int alto1, t_pixel*** imagen2, int ancho2, int alto2, t_pixel color)
{
    int nuevo_ancho = ancho1 + ancho2;
    int nuevo_alto = (alto1 > alto2) ? alto1 : alto2;

    // Crear la nueva imagen con el tamaño combinado
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

    // Copiar los píxeles de la primera imagen
    for (int i = 0; i < alto1; i++)
    {
        for (int j = 0; j < ancho1; j++)
        {
            nueva_imagen[i][j] = (*imagen1)[i][j];
        }
    }

    // Rellenar el resto de la primera imagen si es más pequeña
    if (alto1 < nuevo_alto)
    {
        for (int i = alto1; i < nuevo_alto; i++)
        {
            for (int j = 0; j < ancho1; j++)
            {
                nueva_imagen[i][j] = color;
            }
        }
    }

    // Copiar los píxeles de la segunda imagen
    for (int i = 0; i < alto2; i++)
    {
        for (int j = 0; j < ancho2; j++)
        {
            nueva_imagen[i][j + ancho1] = (*imagen2)[i][j];
        }
    }

    // Rellenar el resto de la segunda imagen si es más pequeña
    if (alto2 < nuevo_alto)
    {
        for (int i = alto2; i < nuevo_alto; i++)
        {
            for (int j = 0; j < ancho2; j++)
            {
                nueva_imagen[i][j + ancho1] = color;
            }
        }
    }

    // Liberar la memoria de las imágenes originales
    for (int i = 0; i < alto1; i++)
    {
        free((*imagen1)[i]);
    }
    free(*imagen1);

    for (int i = 0; i < alto2; i++)
    {
        free((*imagen2)[i]);
    }
    free(*imagen2);

    // Asignar la nueva imagen a la imagen original
    *imagen1 = nueva_imagen;
}
