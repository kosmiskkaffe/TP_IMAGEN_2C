#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funciones_alvarez.h"


void mover_cursor(FILE* archivo, int cant_posicion)
{
    unsigned char aux;
    for(int i = 0; i <cant_posicion; i++)
    {
        fread(&aux, sizeof(unsigned char), 1, archivo);
    }
}

bool es_opcion_valida(const char* opcion)
{
    return strcmp(opcion, "--negativo") == 0 || strcmp(opcion, "--escala-de-grises") == 0 || strcmp(opcion, "--aumentar-contraste=10") == 0 || strcmp(opcion, "--reducir-contraste=20") == 0 || strcmp(opcion, "--tonalidad-azul=50") == 0
           || strcmp(opcion, "--tonalidad-verde=5") == 0 || strcmp(opcion, "--tonalidad-roja=15") == 0 || strcmp(opcion, "--espejar-horizontal") == 0 || strcmp(opcion, "--espejar-vertical") == 0 || strcmp(opcion, "--recortar=30") == 0
           || strcmp(opcion, "--rotar-derecha") == 0 || strcmp(opcion, "--rotar-izquierda") == 0 || strcmp(opcion, "--achicar=10") == 0 || strcmp(opcion, "--concatenar-horizontal") == 0 || strcmp(opcion, "--concatenar-vertical") == 0
           || strcmp(opcion, "--comodin") == 0;
}

bool es_duplicado(char* archivo, char** archivos_procesados, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(archivo, archivos_procesados[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

const char* obtener_nombre_opcion(const char* opcion)
{
    if (strcmp(opcion, "--negativo") == 0)
    {
        return "negativo";
    }
    else if (strcmp(opcion, "--escala-de-grises") == 0)
    {
        return "escala_de_grises";
    }
    else if (strcmp(opcion, "--aumentar-contraste=10") == 0)
    {
        return "aumentar_contraste_10";
    }
    return "";
}

t_metadata obtener_metadata(FILE* archivo)
{
    t_metadata metadata;
    mover_cursor(archivo, 0);

    // Leer tipo de archivo
    if (fread(&metadata.tipo, sizeof(unsigned short), 1, archivo) != 1)
    {
        perror("Error leyendo tipo de archivo en obtener_metadata");
        return metadata;
    }
    printf("tipo: %u\n", metadata.tipo);

    // Leer tamaño del archivo
    if (fread(&metadata.tamArchivo, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo tamArchivo en obtener_metadata");
        return metadata;
    }
    printf("tamArchivo: %u\n", metadata.tamArchivo);

    // Leer campos reservados
    if (fread(&metadata.reservado1, sizeof(unsigned short), 1, archivo) != 1 ||
            fread(&metadata.reservado2, sizeof(unsigned short), 1, archivo) != 1)
    {
        perror("Error leyendo campos reservados en obtener_metadata");
        return metadata;
    }
    printf("reservado1: %u\n", metadata.reservado1);

    // Leer offset
    if (fread(&metadata.offset, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo offset en obtener_metadata");
        return metadata;
    }
    printf("offset: %u\n", metadata.offset);

    // Leer tamaño del encabezado
    if (fread(&metadata.tamEncabezado, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo tamEncabezado en obtener_metadata");
        return metadata;
    }
    printf("tamEncabezado: %u\n", metadata.tamEncabezado);

    // Leer ancho y alto de la imagen
    if (fread(&metadata.ancho, sizeof(int), 1, archivo) != 1 ||
            fread(&metadata.alto, sizeof(int), 1, archivo) != 1)
    {
        perror("Error leyendo dimensiones en obtener_metadata");
        return metadata;
    }
    printf("ancho: %u\n", metadata.ancho);
    printf("alto: %u\n", metadata.alto);

    // Leer planos y profundidad
    if (fread(&metadata.planos, sizeof(unsigned short), 1, archivo) != 1 ||
            fread(&metadata.profundidad, sizeof(unsigned short), 1, archivo) != 1)
    {
        perror("Error leyendo planos o profundidad en obtener_metadata");
        return metadata;
    }
    printf("planos: %u\n", metadata.planos);
    printf("profundidad: %u\n", metadata.profundidad);

    // Leer compresión y tamaño de la imagen
    if (fread(&metadata.compresion, sizeof(unsigned int), 1, archivo) != 1 ||
            fread(&metadata.tamImagen, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo compresión o tamaño de la imagen en obtener_metadata");
        return metadata;
    }
    printf("compresion: %u\n", metadata.compresion);
    printf("tamImagen: %u\n", metadata.tamImagen);

    // Leer resolución y colores
    if (fread(&metadata.resolucionX, sizeof(int), 1, archivo) != 1 ||
            fread(&metadata.resolucionY, sizeof(int), 1, archivo) != 1 ||
            fread(&metadata.coloresUsados, sizeof(unsigned int), 1, archivo) != 1 ||
            fread(&metadata.coloresImportantes, sizeof(unsigned int), 1, archivo) != 1)
    {
        perror("Error leyendo resolución o colores en obtener_metadata");
        return metadata;
    }
    printf("resolucionX: %u\n", metadata.resolucionX);
    printf("resolucionY: %u\n", metadata.resolucionY);
    printf("coloresUsados: %u\n", metadata.coloresUsados);
    printf("coloresImportantes: %u\n", metadata.coloresImportantes);

    return metadata;
}


void guardar_imagen(FILE* archivo, t_pixel** imagen, int ancho, int alto, t_metadata metadata)
{
    // Escribir encabezado BMP
    fwrite(&metadata.tipo, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.tamArchivo, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.reservado1, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.reservado2, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.offset, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.tamEncabezado, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.ancho, sizeof(int), 1, archivo);
    fwrite(&metadata.alto, sizeof(int), 1, archivo);
    fwrite(&metadata.planos, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.profundidad, sizeof(unsigned short), 1, archivo);
    fwrite(&metadata.compresion, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.tamImagen, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.resolucionX, sizeof(int), 1, archivo);
    fwrite(&metadata.resolucionY, sizeof(int), 1, archivo);
    fwrite(&metadata.coloresUsados, sizeof(unsigned int), 1, archivo);
    fwrite(&metadata.coloresImportantes, sizeof(unsigned int), 1, archivo);

    // Escribir datos adicionales (84 bytes para BMPv5)
    unsigned char datos_adicionales[84] = {0}; // Inicializar con ceros o con los datos correspondientes
    fwrite(datos_adicionales, sizeof(unsigned char), 84, archivo);

    // Calcular el tamaño de una fila y el relleno necesario
    int rowSize = ancho * 3; // 3 bytes por píxel (RGB)
    int padding = (4 - (rowSize % 4)) % 4;

    // Escribir datos de la imagen
    unsigned char paddingBytes[3] = {0, 0, 0}; // Máximo 3 bytes de relleno

    for (int i = 0; i <alto; i++)   // Almacena los píxeles
    {
        for (int j = 0; j < ancho; j++)
        {
            fwrite(&imagen[i][j], sizeof(t_pixel), 1, archivo);
        }

        // Escribir los bytes de relleno
        fwrite(paddingBytes, sizeof(unsigned char), padding, archivo);
    }
}



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










