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
    if (personasABB == NULL || (personasABB->izq == NULL && personasABB->der == NULL)) {
        return;
    }

    if (personasABB->izq != NULL) {
	liberarTPersona(personasABB->izq->persona);
        delete personasABB->izq;
	personasABB->izq = NULL;
    }

    if (personasABB->der != NULL) {
	liberarTPersona(personasABB->der->persona);
        delete personasABB->der;
	personasABB->der = NULL;
    }

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
   
}

nat cantidadTPersonasABB(TPersonasABB personasABB) {
    return 0;
}

TPersona maxIdPersona(TPersonasABB personasABB) {
    return NULL;
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
