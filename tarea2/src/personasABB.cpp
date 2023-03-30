#include "../include/personasABB.h"

struct rep_personasAbb {
    rep_personasAbb *izq;
    TPersona persona;
    rep_personasAbb *der;
};

TPersonasABB crearTPersonasABB() {
    TPersonasABB nuevoArbol = NULL;
    return nuevoArbol;
}

bool esVacioTPersonasABB(TPersonasABB personasABB) { 
    return personasABB == NULL;
}

void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p) {
    if (personasABB == NULL) {
        personasABB = new rep_personasAbb;
	personasABB->persona = p;
	personasABB->izq = NULL;
	personasABB->der = NULL;
    } else if (idTPersona(p) < idTPersona(personasABB->persona)) {
        insertarTPersonasABB(personasABB->izq, p);
    } else if (idTPersona(p) > idTPersona(personasABB->persona)) {
        insertarTPersonasABB(personasABB->der, p);
    };
}

void liberarNodoTPersonasABB(TPersonasABB &personasABB) {
    liberarTPersona(personasABB->persona);
    delete personasABB;
    personasABB = NULL;
}

void liberarTPersonasABB(TPersonasABB &personasABB) {
    if (personasABB == NULL) {
        return;
    }

    liberarTPersonasABB(personasABB->izq);
    liberarTPersonasABB(personasABB->der);
    liberarNodoTPersonasABB(personasABB);
}

void imprimirTPersonasABB(TPersonasABB personasABB) {
  if (personasABB == NULL) {
      return;
  }

  imprimirTPersonasABB(personasABB->izq);
  imprimirTPersona(personasABB->persona);
  imprimirTPersonasABB(personasABB->der);
}

nat cantidadTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL) {
        return 0;
    }    
    
    return 1 + cantidadTPersonasABB(personasABB->izq) + cantidadTPersonasABB(personasABB->der);
}

TPersona maxIdPersona(TPersonasABB personasABB) {
    while (personasABB != NULL && personasABB->der != NULL) {
    	personasABB = personasABB->der;
    }

    return personasABB->persona;
}

void removerTPersonasABB(TPersonasABB &personasABB, nat id) {
    
}

bool estaTPersonasABB(TPersonasABB personasABB, nat id) {
    return false;
}

TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id) {
    return NULL;
}

nat alturaTPersonasABB(TPersonasABB personasABB) {
    return 0;
}

bool esPerfectoTPersonasABB(TPersonasABB personasABB) {
    return false;
}

TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad) {
    return NULL;
}

TPersonasLDE aTPersonasLDE(TPersonasABB personasABB) {
    return NULL;
}
