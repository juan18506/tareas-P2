#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona * colaPrioridad;
  TPersona * idPersonas;
  nat tope;
  nat cantidad;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona cp = new rep_colaDePrioridadPersona;
  cp->colaPrioridad = new TPersona[N + 1];
  cp->idPersonas = new TPersona[N + 1];
  cp->cantidad = N + 1;
  cp->tope = 0;

  for (nat i = 0; i < N + 1; i++) {
    cp->colaPrioridad[i] = NULL;
    cp->idPersonas[i] = NULL;
  }

  return cp;
}

TFecha obtenerFechaPrioridad(TPersona persona) {
  return fechaTEvento(primerEventoDeTPersona(persona));
}

void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp) {
  TPersona personaPosOG = cp->colaPrioridad[pos];

  while (pos > 1 && compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos]), obtenerFechaPrioridad(cp->colaPrioridad[pos / 2])) == -1) {
    cp->colaPrioridad[pos] = cp->colaPrioridad[pos / 2];
    cp->colaPrioridad[pos / 2] = personaPosOG;
    pos = pos / 2;
  };
}

void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp) {
  cp->colaPrioridad[pos] = cp->colaPrioridad[cp->tope + 1];
  nat posMenor = 0;

  while (pos * 2 <= cp->tope) {
    // hijo derecho > hijo izquierdo (prioridad)
    if (pos * 2 + 1 <= cp->tope && compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos * 2 + 1]), obtenerFechaPrioridad(cp->colaPrioridad[pos * 2])) == -1) {
      posMenor = pos * 2 + 1;
    } else {
      posMenor = pos * 2;
    }
    
    // padre > hijo (prioridad)
    if (compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos]), obtenerFechaPrioridad(cp->colaPrioridad[posMenor])) <= 0) {
      return;
    }

    TPersona copiaPersonaOG = cp->colaPrioridad[pos];
    cp->colaPrioridad[pos] = cp->colaPrioridad[posMenor];
    cp->colaPrioridad[posMenor] = copiaPersonaOG;
    pos = posMenor;
  };
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {

}

void liberarCP(TColaDePrioridadPersona &cp) {
  for (nat i = 1; i <= cp->tope; i++) {
    liberarTPersona(cp->colaPrioridad[i]);
  }

  delete [] cp->colaPrioridad;
  cp->colaPrioridad = NULL;
  delete [] cp->idPersonas;
  cp->idPersonas = NULL;
  delete cp;
  cp = NULL;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  if (cp->tope + 1 >= cp->cantidad) {
    return;
  }
  
  cp->colaPrioridad[cp->tope + 1] = persona;
  filtrado_ascendente(cp->tope + 1, cp);

  cp->idPersonas[idTPersona(persona)] = persona;
  cp->tope++;
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return cp->tope == 0;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->colaPrioridad[1];
} 

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  if (estaVaciaCP(cp)) {
    return;
  }

  cp->idPersonas[idTPersona(cp->colaPrioridad[1])] = NULL;
  liberarTPersona(cp->colaPrioridad[1]);
  cp->colaPrioridad[1] = NULL;
  cp->tope--;
  filtrado_descendente(1, cp);
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  if (id < 1 || id >= cp->cantidad) {
    return false;
  }

  return cp->idPersonas[id] != NULL;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp) {
  return obtenerFechaPrioridad(cp->idPersonas[id]);
}