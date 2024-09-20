#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funciones_sarabia.h"

void aumentar_rojo(t_pixel** imagen, int ancho, int alto,int nivel)
{
    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            int nuevo_valor = imagen[i][j].pixel[2] + imagen[i][j].pixel[2] * nivel/ 100;
            if (nuevo_valor > 255) nuevo_valor = 255; // Me aseguro de que no exceda 255
            imagen[i][j].pixel[2] = nuevo_valor;
        }
    }
}

void espejar_vertical(t_pixel** imagen, int ancho, int alto)
{
    for (int i = 0; i < alto / 2; i++)
    {
        for (int j = 0; j < ancho; j++)
        {
            t_pixel temp = imagen[i][j];
            imagen[i][j] = imagen[alto - 1 - i][j];
            imagen[alto - 1 - i][j] = temp;
        }
    }
}

void rotar_derecha(t_pixel*** imagen, int* ancho, int* alto)
{
    int nuevo_ancho = *alto;
    int nuevo_alto = *ancho;

    // Crear una nueva imagen con dimensiones intercambiadas
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

    // Rellenar la nueva imagen con los píxeles rotados
    for (int i = 0; i < *alto; i++)
    {
        for (int j = 0; j < *ancho; j++)
        {
            nueva_imagen[j][*alto - 1 - i] = (*imagen)[i][j];
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

void rotar_izquierda(t_pixel*** imagen, int* ancho, int* alto)
{
    int nuevo_ancho = *alto;
    int nuevo_alto = *ancho;

    // Creo una nueva imagen con dimensiones intercambiadas
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

    // Relleno la nueva imagen con los píxeles rotados
    for (int i = 0; i < *alto; i++)
    {
        for (int j = 0; j < *ancho; j++)
        {
            nueva_imagen[*ancho - 1 - j][i] = (*imagen)[i][j];
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

void concatenar_horizontal(t_pixel*** imagen1, int ancho1, int alto1, t_pixel*** imagen2, int ancho2, int alto2, t_pixel color)
{
    int nuevo_ancho = (ancho1 > ancho2) ? ancho1 : ancho2;
    int nuevo_alto = alto1 + alto2;

    // Creo la nueva imagen con el tamaño combinado
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

    // Copio los píxeles de la primera imagen
    for (int i = 0; i < alto1; i++)
    {
        for (int j = 0; j < ancho1; j++)
        {
            nueva_imagen[i][j] = (*imagen1)[i][j];
        }
    }

    // Relleno el resto de la primera imagen si es más pequeña
    if (ancho1 < nuevo_ancho)
    {
        for (int i = 0; i < alto1; i++)
        {
            for (int j = ancho1; j < nuevo_ancho; j++)
            {
                nueva_imagen[i][j] = color;
            }
        }
    }

    // Copio los píxeles de la segunda imagen
    for (int i = 0; i < alto2; i++)
    {
        for (int j = 0; j < ancho2; j++)
        {
            nueva_imagen[i + alto1][j] = (*imagen2)[i][j];
        }
    }

    // Relleno el resto de la segunda imagen si es más pequeña
    if (ancho2 < nuevo_ancho)
    {
        for (int i = 0; i < alto2; i++)
        {
            for (int j = ancho2; j < nuevo_ancho; j++)
            {
                nueva_imagen[i + alto1][j] = color;
            }
        }
    }

    // Libero la memoria de las imágenes originales
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

    // Asigno la nueva imagen a la imagen original
    *imagen1 = nueva_imagen;
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
