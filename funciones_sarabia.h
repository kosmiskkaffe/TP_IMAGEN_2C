#ifndef FUNCIONES_SARABIA_H_INCLUDED
#define FUNCIONES_SARABIA_H_INCLUDED
#include "funciones_grupo.h"

void aumentar_rojo(t_pixel** imagen, int ancho, int alto,int nivel); // Aumenta en un 15% la intensidad del color rojo
void espejar_vertical(t_pixel** imagen, int ancho, int alto); // Invierte la imagen verticalmente
void rotar_derecha(t_pixel*** imagen, int* ancho, int* alto,t_metadata* metadata); // Gira la imagen 90 grados a la derecha (sentido horario) - Tengo problemas en la asignación de memoria
void rotar_izquierda(t_pixel*** imagen, int* ancho, int* alto,t_metadata* metadata); // Gira la imagen 90 grados a la izquierda (sentido antihorario) - Tengo problemas en la asignación de memoria

#endif // FUNCIONES_SARABIA_H_INCLUDED
