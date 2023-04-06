/*
  Módulo de definición de 'personasABB'.

  Los estructura de tipo personasABB es un arbol binario de búsqueda que almacena a las personas por id. .

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef PERSONASABB_H
#define PERSONASABB_H

#include "personasLDE.h"

// Definición de tipo TPersonasABB como un puntero a rep_personasAbb
typedef struct rep_personasAbb* TPersonasABB;

// Función para crear un nuevo árbol binario
// Devuelve un nuevo árbol binario vacío
// La funcion es Theta(1) peor caso
TPersonasABB crearTPersonasABB();

// Función para determinar si un árbol binario es vacío
// Devuelve true si el árbol binario es vacío, false en caso contrario
// La funcion es Theta(1) pero caso
bool esVacioTPersonasABB(TPersonasABB personasABB);

// Función para insertar una persona en el árbol binario ordenado por id
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
// PRE: la persona no está en el árbol binario
void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p);

// Función para liberar la memoria asignada a un árbol binario
// La función es O(n*m) peor caso, donde n es la cantidad de personas en el árbol y m es la cantidad de eventos de la agenda con mas eventos entre todas las personas del árbol.
void liberarTPersonasABB(TPersonasABB &personasABB);

// Función para imprimir las personas del árbol binario en orden de id
// La función es O(n*m) peor caso, donde n es la cantidad de personas en el árbol y m es la cantidad de eventos de la agenda con mas eventos entre todas las personas del árbol.
void imprimirTPersonasABB(TPersonasABB personasABB);

// Función para obtener la cantidad de personas en el árbol binario
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
nat cantidadTPersonasABB(TPersonasABB personasABB);

// Función para obtener la persona con el id más grande del árbol binario
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
// PRE: el árbol binario no es vacío
TPersona maxIdPersona(TPersonasABB personasABB);

// Función para eliminar una persona del árbol binario
// En caso de que el nodo a remover tenga ambos subárboles no vacíos,
// se reemplaza por la Persona con el id más grande del subárbol izquierdo. 
// La función es Theta(n+m) peor caso, donde n es la cantidad de personas en el árbol y m es la cantidad de eventos de la agenda de la perosna a remover.
// PRE: la persona está en el árbol binario
void removerTPersonasABB(TPersonasABB &personasABB, nat id);

// Función que determina si una persona está en el árbol binario
// Devuelve true si la persona está en el árbol binario, false en caso contrario
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
bool estaTPersonasABB(TPersonasABB personasABB, nat id);

// Función para obtener una persona del árbol binario
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
// PRE: la persona está en el árbol binario
TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id);

// Funcion para obtener la altura del árbol binario
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
nat alturaTPersonasABB(TPersonasABB personasABB);

// Función para determinar si el árbol binario es perfecto
// Devuelve true si el árbol binario es perfecto, false en caso contrario
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
bool esPerfectoTPersonasABB(TPersonasABB personasABB);

// Función que retorna un nuevo TPersonasABB con las personas de personasABB que son mayores a cierta edad
// El árbol retornado NO comparte memoria con el árbol pasado por parámetro.
// En caso de que deba elegir un nuevo nodo como raíz seleccione el nodo con el id más grande del 
// subárbol izquierdo.
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad);

// Función que retorna una lista de tipo TPersonasLDE con las personas que están en el árbol pasado por parámetro
// La lista debe estar ordenada por id.
// La lista resultado NO comparte memoria con el árbol pasado por parámetro.
// La funcion es Theta(n) peor caso, siendo n la cantidad de personas en el árbol binario
TPersonasLDE aTPersonasLDE(TPersonasABB personasABB);

#endif  // PERSONASABB_H