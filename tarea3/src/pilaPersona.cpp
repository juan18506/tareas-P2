#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct nodoPila {
  TPersonasLDE listaPersonas;
  nodoPila * sig;
};

struct rep_pilaPersona {
  nodoPila * pila;
  unsigned int cantidad;
};

TPilaPersona crearTPilaPersona() {
  TPilaPersona nuevaPila = new rep_pilaPersona;
  nuevaPila->pila = NULL;
  nuevaPila->cantidad = 0;
  return nuevaPila;
}

void liberarTPilaPersona(TPilaPersona &p) {
  while (p->cantidad != 0) {
    desapilarDeTPilaPersona(p);
  }

  delete p;
  p = NULL;
}

nat cantidadEnTPilaPersona(TPilaPersona p) { 
  return p->cantidad;
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona) {
  nodoPila * nuevo = new nodoPila;
  nuevo->listaPersonas = crearTPersonasLDE();
  insertarInicioDeTPersonasLDE(nuevo->listaPersonas, persona);
  nuevo->sig = p->pila;
  p->pila = nuevo;
  p->cantidad++;
}

TPersona cimaDeTPilaPersona(TPilaPersona p) { 
  return p->pila->listaPersonas;
}

void desapilarDeTPilaPersona(TPilaPersona &p) {
  nodoPila * aBorrar = p->pila;
  p->pila = p->pila->sig;
  liberarTPersonasLDE(aBorrar->listaPersonas);
  p->cantidad--;
}
