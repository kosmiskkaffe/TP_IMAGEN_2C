#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED

#include <stdbool.h>
#include <string.h>
#include <stdio.h>


typedef struct
{
    unsigned char pixel[3];
} t_pixel;

typedef struct
{
    unsigned short tipo;        // Tipo de archivo (debe ser 'BM')
    unsigned int tamArchivo;    // Tamaño del archivo en bytes
    unsigned short reservado1;  // Reservado (debe ser 0) - No se usa
    unsigned short reservado2;  // Reservado (debe ser 0) - No se usa
    unsigned int offset;        // Offset donde comienzan los datos de la imagen
    unsigned int tamEncabezado; // El tamaño de esta cabecera (40 bytes)
    int ancho;                  // Ancho de la imagen
    int alto;                   // Alto de la imagen
    unsigned short planos;      // Número de planos de color (debe ser 1)
    unsigned short profundidad; // Bits por pixel (24 para RGB)
    unsigned int compresion;    // El tipo de compresión (0 para sin compresión)
    unsigned int tamImagen;     // El tamaño de los datos de la imagen
    int resolucionX;            // Es es la resolución horizontal (píxeles por metro)
    int resolucionY;            // Es la resolución vertical (píxeles por metro)
    unsigned int coloresUsados; // Número de los colores en la paleta (0 para todos)
    unsigned int coloresImportantes; // Número de los colores importantes (0 para todos)
} t_metadata;

int solucion(int argc, char* argv[]);
t_metadata obtener_metadata(FILE* archivo); //  OK
void mover_cursor(FILE* archivo, int cant_posicion); //  OK - Para posicionarme en la imagen
void guardar_imagen(FILE* archivo,t_pixel** imagen, int ancho, int alto, t_metadata metadata); //Guardar copia de la Imagen
int calcRelleno(unsigned int); // Calcular padding
bool es_opcion_valida(const char* opcion); // Opciones válidas
const char* obtener_nombre_opcion(const char* opcion); //Formatear nombre en la copia del archivo de la Imagen
bool es_duplicado(char* archivo, char** archivos_procesados, int count); //Controlar que no ejecute dos veces una misma opcion en el argumento


#endif // FUNCIONES_GRUPO_H_INCLUDED
