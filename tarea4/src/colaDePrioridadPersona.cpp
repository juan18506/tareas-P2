#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona * colaPersona;
  nat tope;
  nat cantidad;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona cp = new rep_colaDePrioridadPersona;
  cp->colaPersona = new TPersona[N + 1];
  cp->cantidad = N + 1;
  cp->tope = 0;

  for (nat i = 0; i < N + 1; i++) {
    cp->colaPersona[i] = NULL;
  }

  return cp;
}

TFecha obtenerFechaPrioridad(TPersona persona) {
  return fechaTEvento(primerEventoDeTPersona(persona));
}

void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp) {
  TPersona personaPosOG = cp->colaPersona[pos];

  while (pos > 1 && compararTFechas(obtenerFechaPrioridad(cp->colaPersona[pos]), obtenerFechaPrioridad(cp->colaPersona[pos / 2])) == -1) {
    cp->colaPersona[pos] = cp->colaPersona[pos / 2];
    cp->colaPersona[pos / 2] = personaPosOG;
    pos = pos / 2;
  };
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {

}

void liberarCP(TColaDePrioridadPersona &cp) {
  for (nat i = 1; i <= cp->tope; i++) {
    liberarTPersona(cp->colaPersona[i]);
  }
  
  delete [] cp->colaPersona;
  cp->colaPersona = NULL;
  delete cp;
  cp = NULL;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  if (cp->tope + 1 >= cp->cantidad) {
    return;
  }
  
  cp->colaPersona[cp->tope + 1] = persona;
  filtrado_ascendente(cp->tope + 1, cp);
  cp->tope++;
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return cp->tope == 0;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return NULL;
} 

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  
}

// TODO: O(n) => O(1) 
bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  for (nat i = 1; i <= cp->tope; i++) {
    if (idTPersona(cp->colaPersona[i]) == id) {
      return true;
    }
  }

  return false;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp) {
  return NULL;
}