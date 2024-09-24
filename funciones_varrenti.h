#ifndef FUNCIONES_VARRENTI_H_INCLUDED
#define FUNCIONES_VARRENTI_H_INCLUDED
#include "funciones_grupo.h"

void aumentar_verde(t_pixel** imagen, int ancho, int alto,int nivel); //  Aumenta en un 5% la intensidad del color verde
void espejar_horizontal(t_pixel** imagen, int ancho, int alto); // Invierte horizontalmente la imagen
void recortar_30(t_pixel*** imagen, int* ancho, int* alto, t_metadata* metadata); // Reduce el tamaño de la imagen al 30%, sin cambiar sus proporciones. Obs: Tengo un problema de asignacion de memoria
void achicar_10(t_pixel*** imagen, int* ancho, int* alto,t_metadata* metadata); // Reduce la imagen al 10%.

// Función propuesta por el grupo
void comodin_aplicar_desenfoque(t_pixel*** imagen, int ancho, int alto); // Funciona OK. Comodin : Aplicamos un desenfoque a la Imagen

#endif // FUNCIONES_VARRENTI_H_INCLUDED
