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
    unsigned int tamArchivo;    // Tama�o del archivo en bytes
    unsigned short reservado1;  // Reservado (debe ser 0) - No se usa
    unsigned short reservado2;  // Reservado (debe ser 0) - No se usa
    unsigned int offset;        // Offset donde comienzan los datos de la imagen
    unsigned int tamEncabezado; // El tama�o de esta cabecera (40 bytes)
    int ancho;                  // Ancho de la imagen
    int alto;                   // Alto de la imagen
    unsigned short planos;      // N�mero de planos de color (debe ser 1)
    unsigned short profundidad; // Bits por pixel (24 para RGB)
    unsigned int compresion;    // El tipo de compresi�n (0 para sin compresi�n)
    unsigned int tamImagen;     // El tama�o de los datos de la imagen
    int resolucionX;            // Es es la resoluci�n horizontal (p�xeles por metro)
    int resolucionY;            // Es la resoluci�n vertical (p�xeles por metro)
    unsigned int coloresUsados; // N�mero de los colores en la paleta (0 para todos)
    unsigned int coloresImportantes; // N�mero de los colores importantes (0 para todos)
} t_metadata;

int solucion(int argc, char* argv[]);
t_metadata obtener_metadata(FILE* archivo); // Funciona OK
void mover_cursor(FILE* archivo, int cant_posicion); // Funciona OK - Para posicionarme en la imagen
void guardar_imagen(FILE* archivo,t_pixel** imagen, int ancho, int alto, t_metadata metadata); //Guardar copia de la Imagen
bool es_opcion_valida(const char* opcion); // Opciones v�lidas
const char* obtener_nombre_opcion(const char* opcion); //Formatear nombre en la copia del archivo de la Imagen
bool es_duplicado(char* archivo, char** archivos_procesados, int count); //Controlar que no ejecute dos veces una misma opcion en el argumento

void negativo(t_pixel** imagen, int ancho, int alto); // Negativo
void escala_de_grises(t_pixel** imagen, int ancho, int alto); // Promedia los valores de cada color RGB y transformarlo a gris
void aumentar_contraste(t_pixel** imagen, int ancho, int alto, int nivel); //Aumenta el conttraste en un 10%
void reducir_contraste(t_pixel** imagen, int ancho, int alto, int nivel); // Reduce el contraste en un 20%
void aumentar_azul(t_pixel** imagen, int ancho, int alto,int nivel); // Aumenta en un 50% la intensidad del color azul


#endif // FUNCIONES_ALVAREZ_H_INCLUDED
