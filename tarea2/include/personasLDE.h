/*
  Módulo de definición de 'personasLDE'.

  La estructura de tipo personasLDD es un lista doblemente encadenada de personas con puntero al inicio y al final de la lista.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef PERSONASLDE_H
#define PERSONASLDE_H

#include "persona.h"
#include "utils.h"

// Definición de tipo TPersonasLDE como un puntero a rep_personasLDE
typedef struct rep_personasLDE *TPersonasLDE;

// Función para crear una nueva lista vacía de personas
TPersonasLDE crearTPersonasLDE();

// Función para insertar una persona en la lista de personas en una posición dada
// Si pos es 1, la persona se inserta al inicio de la lista
// Si pos es mayor que la cantidad de personas en la lista, la persona se inserta al final de la lista
// La función es Theta(n) peor caso, siendo n la cantidad de personas en la lista
// PRE: pos >= 1
void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos);

// Función para liberar la memoria asignada a una lista de personas
// La función es Theta(n) peor caso
void liberarTPersonasLDE(TPersonasLDE &personas);

// Función para imprimir secuencialmente las personas de la lista de personas
// La función es O(n*m) peor caso, donde n es la cantidad de personas en la lista y m es la cantidad de eventos de la agenda con mas eventos entre todas las personas de la lista.
void imprimirTPersonasLDE(TPersonasLDE personas);

// Función para obtener la cantidad de personas en la lista de personas
// La función es Theta(1) peor caso
nat cantidadTPersonasLDE(TPersonasLDE personas);

// Función para eliminar una persona del inicio de la lista de personas
// La función es Theta(1) peor caso
// Si no hay personas en la lista la función no hace nada
void eliminarInicioTPersonasLDE(TPersonasLDE &personas);

// Función para eliminar una persona del final de la lista de personas
// La función es Theta(1) peor caso
// Si no hay personas en la lista la función no hace nada
void eliminarFinalTPersonasLDE(TPersonasLDE &personas);

// Función para verificar si un elemento de tipo TPersona existe en una lista de personas
// Devuelve true si existe, false en caso contrario
// La función es Theta(n) peor caso, siendo n la cantidad de personas en la lista
bool estaEnTPersonasLDE(TPersonasLDE personas, nat id);

// Función para obtener una persona en la lista de personas
// La función es Theta(n) peor caso, siendo n la cantidad de personas en la lista
// PRE: la persona existe en la lista
TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id);

// Función que recibe dos listas de personas y las concatena en una NUEVA lista.
// Al final de la función se libera la memoria de las listas originales.
// La función es Theta(1) peor caso
TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2);

#endif  // PERSONASLDE_H
