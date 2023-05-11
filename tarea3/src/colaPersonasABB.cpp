#include "../include/colaPersonasABB.h"
#include "../include/personasLDE.h"

struct rep_nodoCola {
  TPersonasABB arbol;
  rep_nodoCola * sig;
};
struct rep_colaPersonasABB {
  rep_nodoCola * inicio;
  rep_nodoCola * final;
  nat cantidad;
};

TColaPersonasABB crearTColaPersonasABB() {
  TColaPersonasABB nuevaCola = NULL;
  nuevaCola = new rep_colaPersonasABB;

  nuevaCola->inicio = NULL;
  nuevaCola->final = NULL;
  nuevaCola->cantidad = 0;

  return nuevaCola;
}

void liberarTColaPersonasABB(TColaPersonasABB &c) {
  rep_nodoCola * nodoCola = c->inicio;
  rep_nodoCola * aLiberar = c->inicio;

    // Recorrida completa de la cola
    while (nodoCola != NULL) {
        nodoCola = nodoCola->sig;
        delete aLiberar;
        aLiberar = nodoCola;
    }

    delete c;
    c = NULL;
}

nat cantidadEnTColaPersonasABB(TColaPersonasABB c) { 
  return c->cantidad;
}

void encolarEnTColaPersonasABB(TPersonasABB t, TColaPersonasABB &c) {
  rep_nodoCola * nuevo = NULL;
  nuevo = new rep_nodoCola;
  nuevo->arbol = t;
  nuevo->sig = NULL;

  if (c->cantidad == 0) {
    c->inicio = nuevo;
  } else {
    c->final->sig = nuevo;
  }

  c->final = nuevo;
  c->cantidad++;
}

TPersonasABB frenteDeTColaPersonasABB(TColaPersonasABB c) { 
  return c->inicio->arbol;
}

void desencolarDeTColaPersonasABB(TColaPersonasABB &c) {
  rep_nodoCola * copiaInicio = c->inicio;
  c->inicio = c->inicio->sig;
  delete copiaInicio;

  if (c->cantidad == 1) {
    c->final = NULL;
  }

  c->cantidad--;
}
