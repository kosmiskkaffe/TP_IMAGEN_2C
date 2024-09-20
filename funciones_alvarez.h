#ifndef FUNCIONES_ALVAREZ_H_INCLUDED
#define FUNCIONES_ALVAREZ_H_INCLUDED
#include <stdbool.h>

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
t_metadata obtener_metadata(FILE* archivo); // Funciona OK
void mover_cursor(FILE* archivo, int cant_posicion); // Funciona OK - Para posicionarme en la imagen
void guardar_imagen(FILE* archivo,t_pixel** imagen, int ancho, int alto, t_metadata metadata); //Guardar copia de la Imagen
bool es_opcion_valida(const char* opcion); // Opciones válidas
const char* obtener_nombre_opcion(const char* opcion); //Formatear nombre en la copia del archivo de la Imagen
bool es_duplicado(char* archivo, char** archivos_procesados, int count); //Controlar que no ejecute dos veces una misma opcion en el argumento

void negativo(t_pixel** imagen, int ancho, int alto); // Negativo
void escala_de_grises(t_pixel** imagen, int ancho, int alto); // Promedia los valores de cada color RGB y transformarlo a gris
void aumentar_contraste(t_pixel** imagen, int ancho, int alto, int nivel); //Aumenta el conttraste en un 10%
void reducir_contraste(t_pixel** imagen, int ancho, int alto, int nivel); // Reduce el contraste en un 20%
void aumentar_azul(t_pixel** imagen, int ancho, int alto,int nivel); // Aumenta en un 50% la intensidad del color azul


#endif // FUNCIONES_ALVAREZ_H_INCLUDED
