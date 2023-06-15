#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona * colaPrioridad;
  TPersona * idPersonas;
  nat tope;
  nat cantidad;
  bool invertida;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona cp = new rep_colaDePrioridadPersona;
  // Orden por prioridad
  cp->colaPrioridad = new TPersona[N + 1];
  // Orden por IDs
  cp->idPersonas = new TPersona[N + 1];
  cp->cantidad = N + 1;
  cp->tope = 0;
  // Flag para indicar criterio de prioridad en colaPrioridad
  cp->invertida = false;

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
  int valorComparacion = 0;

  // Criterio de prioridad
  if (!cp->invertida) {
    valorComparacion = -1;
  } else {
    valorComparacion = 1;
  }

  // Si no se cumple la prioridad se invierten las posiciones
  while (pos > 1 && compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos]), obtenerFechaPrioridad(cp->colaPrioridad[pos / 2])) == valorComparacion) {
    cp->colaPrioridad[pos] = cp->colaPrioridad[pos / 2];
    cp->colaPrioridad[pos / 2] = personaPosOG;
    pos = pos / 2;
  };
}

void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp) {
  cp->colaPrioridad[pos] = cp->colaPrioridad[cp->tope + 1];
  nat posMenor = 0;
  int valorComparacion = 0;

  // Criterio de prioridad
  if (!cp->invertida) {
    valorComparacion = -1;
  } else {
    valorComparacion = 1;
  }

  // Mientras que existe el hijo izquierdo
  while (pos * 2 <= cp->tope) {
    // hijo derecho > hijo izquierdo (prioridad)
    if (pos * 2 + 1 <= cp->tope && compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos * 2 + 1]), obtenerFechaPrioridad(cp->colaPrioridad[pos * 2])) == valorComparacion) {
      posMenor = pos * 2 + 1;
    } else {
      posMenor = pos * 2;
    }

    // padre > hijo (prioridad)
    if (!cp->invertida) {
      if (compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos]), obtenerFechaPrioridad(cp->colaPrioridad[posMenor])) <= 0) {
        return;
      }
    } else {
      if (compararTFechas(obtenerFechaPrioridad(cp->colaPrioridad[pos]), obtenerFechaPrioridad(cp->colaPrioridad[posMenor])) >= 0) {
        return;
      }
    }

    TPersona copiaPersonaOG = cp->colaPrioridad[pos];
    cp->colaPrioridad[pos] = cp->colaPrioridad[posMenor];
    cp->colaPrioridad[posMenor] = copiaPersonaOG;
    pos = posMenor;
  };
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  TColaDePrioridadPersona nc = crearCP(cp->cantidad);
  nc->invertida = !cp->invertida;
  
  // Recorre toda la cola cp e inserta con el nuevo criterio en nc
  for (nat i = 1; i <= cp->tope; i++) {
    insertarEnCP(cp->colaPrioridad[i], nc);
  }
  
  delete [] cp->colaPrioridad;
  delete [] cp->idPersonas;
  delete cp;
  cp = nc;
}

void liberarCP(TColaDePrioridadPersona &cp) {
  // Recorrida de cp (mismos punteros que idPersonas por eso esta no se libera)
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
  // Caso cp llena
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
  // Caso cp vacia
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
  // Caso id fuera de rango
  if (id < 1 || id >= cp->cantidad) {
    return false;
  }

  return cp->idPersonas[id] != NULL;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp) {
  return obtenerFechaPrioridad(cp->idPersonas[id]);
}