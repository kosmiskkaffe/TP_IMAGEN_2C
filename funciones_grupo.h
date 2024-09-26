#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED

/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Alvarez, Giselé
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
bool validar_nivel(int nivel); //Valida el rango del nivel pasado por parametros (entre 0 y 100)
char *reemplazar_caracteres(char *cadena); // Reeplazar los caracteres '=' y '-' por '_' en el nombre del archivo de salida
bool es_duplicado(char* archivo, char** archivos_procesados, int count); //Controlar que no ejecute dos veces una misma opcion en el argumento


#endif // FUNCIONES_GRUPO_H_INCLUDED
