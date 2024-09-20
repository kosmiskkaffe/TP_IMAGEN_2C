/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Alvarez, Gisele
    DNI: 34579954
    Entrega: Sí
    -----------------
    Apellido: Sarabia, Patricio
    DNI: 32335091
    Entrega: Sí
    -----------------
    Apellido: Varrenti, Pablo Martin
    DNI: 38056239
    Entrega: Sí
    -----------------
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones_alvarez.h"
#include "funciones_sarabia.h"
#include "funciones_varrenti.h"


int solucion(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Uso: bmpmanipuleitor <opcion1> <opcion2> ... <archivo>\n");
        return 1;
    }

    char* archivo_entrada = NULL;
    char* opciones_validas[16]; // Máximo de opciones válidas
    int num_opciones_validas = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strstr(argv[i], ".bmp") != NULL)
        {
            archivo_entrada = argv[i];
        }
        else if (es_opcion_valida(argv[i]))
        {
            int es_duplicado = 0;
            for (int j = 0; j < num_opciones_validas; j++)
            {
                if (strcmp(opciones_validas[j], argv[i]) == 0)
                {
                    es_duplicado = 1;
                    break;
                }
            }
            if (!es_duplicado)
            {
                opciones_validas[num_opciones_validas++] = argv[i];
            }
        }
    }

    if (archivo_entrada == NULL)
    {
        printf("No se especificó un archivo BMP válido.\n");
        return 1;
    }

    FILE* archivo = fopen(archivo_entrada, "rb");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo %s\n", archivo_entrada);
        return 1;
    }

    t_metadata metadata = obtener_metadata(archivo);
    int ancho = metadata.ancho;
    int alto = metadata.alto;

    t_pixel** imagen = (t_pixel**)malloc(sizeof(t_pixel*) * alto);
    if (imagen == NULL)
    {
        perror("Error asignando memoria alto");
        fclose(archivo);
        return 1;
    }

    for (int j = 0; j < alto; j++)
    {
        imagen[j] = (t_pixel*)malloc(sizeof(t_pixel) * ancho);
        if (imagen[j] == NULL)
        {
            perror("Error asignando memoria ancho");
            for (int k = 0; k < j; k++)
            {
                free(imagen[k]);
            }
            free(imagen);
            fclose(archivo);
            return 1;
        }
    }

    for (int j = 0; j < alto; j++)
    {
        if (fread(imagen[j], sizeof(t_pixel), ancho, archivo) != ancho)
        {
            perror("Error leyendo la imagen");
            for (int k = 0; k < alto; k++)
            {
                free(imagen[k]);
            }
            free(imagen);
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);

    for (int i = 0; i < num_opciones_validas; i++)
    {
        t_pixel** imagen_copia = (t_pixel**)malloc(sizeof(t_pixel*) * alto);
        if (imagen_copia == NULL)
        {
            perror("Error asignando memoria alto para copia");
            continue;
        }

        for (int j = 0; j < alto; j++)
        {
            imagen_copia[j] = (t_pixel*)malloc(sizeof(t_pixel) * ancho);
            if (imagen_copia[j] == NULL)
            {
                perror("Error asignando memoria ancho para copia");
                for (int k = 0; k < j; k++)
                {
                    free(imagen_copia[k]);
                }
                free(imagen_copia);
                continue;
            }

            // Copiamos la imagen
            memcpy(imagen_copia[j], imagen[j], sizeof(t_pixel) * ancho);
        }

        if (strcmp(opciones_validas[i], "--negativo") == 0)
        {
            negativo(imagen_copia, ancho, alto);
        }
        else if (strcmp(opciones_validas[i], "--escala-de-grises") == 0)
        {
            escala_de_grises(imagen_copia, ancho, alto);
        }
        else if (strncmp(opciones_validas[i], "--aumentar-contraste=10", 20) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 21);
            //printf("nivel: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 10 como nivel
            aumentar_contraste(imagen_copia, ancho, alto, nivel);
        }
        else if (strncmp(opciones_validas[i], "--reducir-contraste=20", 19) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 20);
            //printf("nivel: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 20 como nivel
            reducir_contraste(imagen_copia, ancho, alto, nivel);
        }
        else if (strncmp(opciones_validas[i], "--tonalidad-azul=50", 16) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 17);
            //printf("nivel: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 50 como nivel
            aumentar_azul(imagen_copia, ancho, alto, nivel);
        }
        else if (strncmp(opciones_validas[i], "--tonalidad-roja=15", 16) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 17);
            //printf("nivel: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 15 como nivel
            aumentar_rojo(imagen_copia, ancho, alto, nivel);
        }
        else if (strncmp(opciones_validas[i], "--tonalidad-verde=5", 17) == 0)
        {
            int nivel = atoi(opciones_validas[i] + 18);
            printf("nivel: Valor %d\n", nivel); //Mensaje depurador - Compruebo que le estoy pasando 5 como nivel
            aumentar_verde(imagen_copia, ancho, alto, nivel);
        }
        else if (strcmp(opciones_validas[i], "--espejar-horizontal") == 0)
        {
            espejar_horizontal(imagen_copia, ancho, alto);
        }
        else if (strcmp(opciones_validas[i], "--espejar-vertical") == 0)
        {
            espejar_vertical(imagen_copia, ancho, alto);
        }
        else if (strcmp(opciones_validas[i], "--recortar=30") == 0)
        {
            recortar_30(imagen_copia, ancho, alto);
        }
        else if (strcmp(opciones_validas[i], "--rotar-derecha") == 0)
        {
            rotar_derecha(&imagen_copia, &ancho, &alto);
        }
        else if (strcmp(opciones_validas[i], "--rotar-izquierda") == 0)
        {
            rotar_izquierda(&imagen_copia, &ancho, &alto);
        }
        else if (strcmp(opciones_validas[i], "--achicar=10") == 0)
        {
            achicar_10(&imagen_copia, &ancho, &alto);
        }
        else if (strcmp(opciones_validas[i], "--comodin") == 0)
        {
            comodin_aplicar_desenfoque(&imagen_copia, ancho, alto);
        }


        char archivo_salida[256];
        // Almaceno la cadena formateada en el búfer archivo_salida
        snprintf(archivo_salida, sizeof(archivo_salida), "IMAGEN_%s_%s", opciones_validas[i] + 2, archivo_entrada);

        archivo = fopen(archivo_salida, "wb");
        if (archivo == NULL)
        {
            printf("No es posible crear el archivo %s\n", archivo_salida);
            for (int j = 0; j < alto; j++)
            {
                free(imagen_copia[j]);
            }
            free(imagen_copia);
            continue;
        }

        // Guardo la imagen con los cambios especificados
        guardar_imagen(archivo, imagen_copia, ancho, alto, metadata);

        fclose(archivo);

        for (int j = 0; j < alto; j++)
        {
            free(imagen_copia[j]);
        }
        free(imagen_copia);
    }

    for (int j = 0; j < alto; j++)
    {
        free(imagen[j]);
    }
    free(imagen);

    return 0;
}
