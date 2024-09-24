#ifndef FUNCIONES_ALVAREZ_H_INCLUDED
#define FUNCIONES_ALVAREZ_H_INCLUDED
#include "funciones_grupo.h"

void negativo(t_pixel** imagen, int ancho, int alto); // Negativo
void escala_de_grises(t_pixel** imagen, int ancho, int alto); // Promedia los valores de cada color RGB y transformarlo a gris
void aumentar_contraste(t_pixel** imagen, int ancho, int alto, int nivel); //Aumenta el conttraste en un 10%
void reducir_contraste(t_pixel** imagen, int ancho, int alto, int nivel); // Reduce el contraste en un 20%
void aumentar_azul(t_pixel** imagen, int ancho, int alto,int nivel); // Aumenta en un 50% la intensidad del color azul


#endif // FUNCIONES_ALVAREZ_H_INCLUDED
