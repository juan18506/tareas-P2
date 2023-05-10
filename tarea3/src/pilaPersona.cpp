#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct rep_pilaPersona {
  TPersonasLDE pila;
};

TPilaPersona crearTPilaPersona() {
  TPilaPersona nuevaPila = new rep_pilaPersona;
  nuevaPila->pila = crearTPersonasLDE();
  return nuevaPila;
}

void liberarTPilaPersona(TPilaPersona &p) {
  liberarTPersonasLDE(p->pila);
  delete p;
  p = NULL;
}

nat cantidadEnTPilaPersona(TPilaPersona p) { 
  return cantidadTPersonasLDE(p->pila);
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona) {
  insertarInicioDeTPersonasLDE(p->pila, copiarTPersona(persona));
}

TPersona cimaDeTPilaPersona(TPilaPersona p) { 
  return obtenerInicioDeTPersonasLDE(p->pila);
}

void desapilarDeTPilaPersona(TPilaPersona &p) {
  eliminarInicioTPersonasLDE(p->pila);
}
