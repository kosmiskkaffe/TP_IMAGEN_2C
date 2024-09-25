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

void rotar_derecha(t_pixel*** imagen, int* ancho, int* alto, t_metadata* metadata)
{
    int nuevo_ancho = *alto;
    int nuevo_alto = *ancho;

    // Creo una nueva imagen con dimensiones intercambiadas
    t_pixel** nueva_imagen = (t_pixel**)malloc(nuevo_alto * sizeof(t_pixel*));
    if (nueva_imagen == NULL)
    {
        perror("Error al asignar memoria para nueva_imagen");
        return;
    }
    for (int i = 0; i < nuevo_alto; i++)
    {
        nueva_imagen[i] = (t_pixel*)malloc(nuevo_ancho * sizeof(t_pixel));
        if (nueva_imagen[i] == NULL)
        {
            perror("Error al asignar memoria para nueva_imagen[i]");
            for (int j = 0; j < i; j++)
            {
                free(nueva_imagen[j]);
            }
            free(nueva_imagen);
            return;
        }
    }

    // Roto la imagen 90 grados en sentido horario
    for (int i = 0; i < nuevo_alto; i++)
    {
        for (int j = 0; j < nuevo_ancho; j++)
        {
            nueva_imagen[i][j] = (*imagen)[*alto - 1 - j][i];
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

    // Actualizo la metadata
    metadata->ancho = nuevo_ancho;
    metadata->alto = nuevo_alto;
    metadata->tamImagen = nuevo_ancho * nuevo_alto * (metadata->profundidad / 8);
    metadata->tamArchivo = metadata->offset + metadata->tamImagen;
}

void rotar_izquierda(t_pixel*** imagen, int* ancho, int* alto, t_metadata* metadata)
{
    int nuevo_ancho = (*alto);
    int nuevo_alto = (*ancho);

    // Asigno memoria para la nueva imagen
    t_pixel** nueva_imagen = (t_pixel**)malloc(nuevo_alto * sizeof(t_pixel*));
    if (nueva_imagen == NULL)
    {
        perror("Error asignando memoria para nueva imagen");
        return;
    }

    for (int i = 0; i < nuevo_alto; i++)
    {
        nueva_imagen[i] = (t_pixel*)malloc(nuevo_ancho * sizeof(t_pixel));
        if (nueva_imagen[i] == NULL)
        {
            perror("Error asignando memoria para nueva imagen");
            for (int j = 0; j < i; j++)
            {
                free(nueva_imagen[j]);
            }
            free(nueva_imagen);
            return;
        }
    }

    //printf("Antes nueva_imagen: %d\n", nueva_imagen);
    // Rotamos la imagen
    for (int i = 0; i < nuevo_alto; i++)
    {
        for (int j = 0; j < nuevo_ancho; j++)
        {
            nueva_imagen[i][j] = (*imagen)[j][*ancho - 1 - i];
        }
    }

    //printf("Después nueva_imagen: %d\n", nueva_imagen);

    // Libero la memoria de la imagen original
    for (int i = 0; i < *alto; i++)
    {
        free((*imagen)[i]);
    }
    free(*imagen);

    //printf("Antes Imagen imagen: %d\n", *imagen);

    // Actualizo los punteros y dimensiones
    *imagen = nueva_imagen;
    *ancho = nuevo_ancho;
    *alto = nuevo_alto;

    //printf("Después Imagen imagen: %d\n", *imagen);

    // Actualizo la metadata
    metadata->ancho = nuevo_ancho;
    metadata->alto = nuevo_alto;

    //printf("Fin");
}
