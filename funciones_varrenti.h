#ifndef FUNCIONES_VARRENTI_H_INCLUDED
#define FUNCIONES_VARRENTI_H_INCLUDED
#include "funciones_alvarez.h"

void aumentar_verde(t_pixel** imagen, int ancho, int alto,int nivel); //  Aumenta en un 5% la intensidad del color verde
void espejar_horizontal(t_pixel** imagen, int ancho, int alto); // Invierte horizontalmente la imagen
void recortar_30(t_pixel** imagen, int ancho, int alto); // No funciona // Reduce el tamaño de la imagen al 30%, sin cambiar sus proporciones. Obs: Tengo un problema de asignacion de memoria
void achicar_10(t_pixel*** imagen, int* ancho, int* alto); // No funciona // Reduce la imagen al 10%.
void concatenar_vertical(t_pixel*** imagen1, int ancho1, int alto1, t_pixel*** imagen2, int ancho2, int alto2, t_pixel color); // Concatena verticalmente dos imagenes pasadas por argumento

#endif // FUNCIONES_VARRENTI_H_INCLUDED
