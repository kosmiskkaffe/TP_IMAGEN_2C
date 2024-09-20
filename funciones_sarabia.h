#ifndef FUNCIONES_SARABIA_H_INCLUDED
#define FUNCIONES_SARABIA_H_INCLUDED
#include "funciones_alvarez.h"

void aumentar_rojo(t_pixel** imagen, int ancho, int alto,int nivel); // Aumenta en un 15% la intensidad del color rojo
void espejar_vertical(t_pixel** imagen, int ancho, int alto); // Invierte la imagen verticalmente
void rotar_derecha(t_pixel*** imagen, int* ancho, int* alto); // No Funciona. Gira la imagen 90 grados a la derecha (sentido horario)
void rotar_izquierda(t_pixel*** imagen, int* ancho, int* alto); //  No Funciona. Gira la imagen 90 grados a la izquierda (sentido antihorario)
void concatenar_horizontal(t_pixel*** imagen1, int ancho1, int alto1, t_pixel*** imagen2, int ancho2, int alto2, t_pixel color); // Concatena horizontalmente dos imagenes pasadas por argumento

// Función propuesta por el grupo
void comodin_aplicar_desenfoque(t_pixel*** imagen, int ancho, int alto); // Funciona OK. Comodin : Aplicamos un desenfoque a la Imagen
#endif // FUNCIONES_SARABIA_H_INCLUDED
