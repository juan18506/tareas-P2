#include "../include/personasABB.h"
#include "../include/colaPersonasABB.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////

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

// Theta(n) donde n es la cantidad de elementos en la agenda.
// PRE: la lista no es NULL.
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
    if (personasABB == NULL) {
        return;
    }

    if (id < idTPersona(personasABB->persona)) {
        removerTPersonasABB(personasABB->izq, id);
    } else if (id > idTPersona(personasABB->persona)) {
        removerTPersonasABB(personasABB->der, id);
    } else {
        if (personasABB->der == NULL) {
            TPersonasABB aBorrar = personasABB;
            personasABB = personasABB->izq;
            liberarNodoTPersonasABB(aBorrar);
	    } else if (personasABB->izq == NULL) {
            TPersonasABB aBorrar = personasABB;
            personasABB = personasABB->der;
            liberarNodoTPersonasABB(aBorrar);
	    } else {
            TPersona maxPersonaIzq = maxIdPersona(personasABB->izq);
            liberarTPersona(personasABB->persona);
            personasABB->persona = copiarTPersona(maxPersonaIzq);
            removerTPersonasABB(personasABB->izq, idTPersona(maxPersonaIzq));
	    }
    }
}

bool estaTPersonasABB(TPersonasABB personasABB, nat id) {
    while (personasABB != NULL && idTPersona(personasABB->persona) != id) {
        if (idTPersona(personasABB->persona) > id) {
            personasABB = personasABB->izq;
        } else {
            personasABB = personasABB->der;
        }
    }

    return personasABB != NULL;
}

TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id) {
    while (idTPersona(personasABB->persona) != id) {
        if (idTPersona(personasABB->persona) > id) {
            personasABB = personasABB->izq;
        } else {
            personasABB = personasABB->der;
        }
    }

    return personasABB->persona;
}

nat alturaTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL) {
        return 0;
    }

    int alturaIzquierda = alturaTPersonasABB(personasABB->izq);
    int alturaDerecha = alturaTPersonasABB(personasABB->der);

    if (alturaIzquierda >= alturaDerecha) {
        return alturaIzquierda + 1;
    } else {
        return alturaDerecha + 1;
    }
}

// Funcion auxiliar que calcula las potencias de 2
nat potenciasDeDos(nat pot) {
    nat resultado = 1;


    for (nat i = 0; i < pot; i++) {
        resultado *= 2;
    }

    return resultado;
}

bool esPerfectoTPersonasABB(TPersonasABB personasABB) {
    if (personasABB == NULL || (personasABB->der == NULL && personasABB->izq == NULL)) {
        return true;
    }

    nat alturaIzq = alturaTPersonasABB(personasABB->izq);
    nat alturaDer = alturaTPersonasABB(personasABB->der);
    nat nodos = cantidadTPersonasABB(personasABB);

    // Un ABB perfecto de altura h tiene (2^(h+1) - 1) nodos
    return (alturaIzq == alturaDer) && (potenciasDeDos(alturaIzq + 1) - 1 == nodos);
}

TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad) {
    TPersonasABB mayoresABB = crearTPersonasABB();

    if (personasABB == NULL) {
        return mayoresABB;
    }

    TPersonasABB mayoresIzq = mayoresTPersonasABB(personasABB->izq, edad);
    TPersonasABB mayoresDer = mayoresTPersonasABB(personasABB->der, edad);

    TPersona raiz = personasABB->persona;

    if (edadTPersona(raiz) > edad) {
        mayoresABB = new rep_personasAbb;
        mayoresABB->persona = copiarTPersona(raiz);
        mayoresABB->izq = mayoresIzq;
        mayoresABB->der = mayoresDer;
    } else if (mayoresIzq == NULL) {
        mayoresABB = mayoresDer;
    } else if (mayoresDer == NULL) {
        mayoresABB = mayoresIzq;
    } else {
        TPersona maxPersonaIzq = maxIdPersona(mayoresIzq);
        mayoresABB = new rep_personasAbb;
        mayoresABB->persona = copiarTPersona(maxPersonaIzq);
        mayoresABB->izq = mayoresIzq;
        mayoresABB->der = mayoresDer;
        removerTPersonasABB(mayoresIzq, idTPersona(maxPersonaIzq));
    }

    return mayoresABB;
}

void aplanarEnListaLDE(TPersonasABB personasABB, TPersonasLDE listaLDE) {
    if (personasABB == NULL) {
        return;
    }

    aplanarEnListaLDE(personasABB->der, listaLDE);
    insertarTPersonasLDE(listaLDE, copiarTPersona(personasABB->persona), 1);
    aplanarEnListaLDE(personasABB->izq, listaLDE);
}

TPersonasLDE aTPersonasLDE(TPersonasABB personasABB) {
    TPersonasLDE nuevaLista = crearTPersonasLDE();
    aplanarEnListaLDE(personasABB, nuevaLista);
    return nuevaLista;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

nat amplitudTPersonasABB(TPersonasABB personasABB) {
    TColaPersonasABB cola = crearTColaPersonasABB();
    nat contadorNodosNivel = 0;
    nat nodosNivelAnterior = 0;
    nat nodosRecorridosNivel = 0;
    nat maximoNodosNivel = 0;

    if (!esVacioTPersonasABB(personasABB)) {
        encolarEnTColaPersonasABB(personasABB, cola);
        nodosNivelAnterior++;
        maximoNodosNivel++;
    }

    while (cantidadEnTColaPersonasABB(cola) > 0) {
        personasABB = frenteDeTColaPersonasABB(cola);
        nodosRecorridosNivel++;

        if (!esVacioTPersonasABB(personasABB->izq)) {
            encolarEnTColaPersonasABB(personasABB->izq, cola);
            contadorNodosNivel++;
        }

        if (!esVacioTPersonasABB(personasABB->der)) {
            encolarEnTColaPersonasABB(personasABB->der, cola);
            contadorNodosNivel++;
        }

        if (nodosNivelAnterior == nodosRecorridosNivel && contadorNodosNivel > maximoNodosNivel) {
            maximoNodosNivel = contadorNodosNivel;
        } 
        
        if (nodosNivelAnterior == nodosRecorridosNivel) {
            nodosNivelAnterior = contadorNodosNivel;
            contadorNodosNivel = 0;
            nodosRecorridosNivel = 0;
        }

        desencolarDeTColaPersonasABB(cola);
    }

    liberarTColaPersonasABB(cola);
    return maximoNodosNivel;
}

TPilaPersona serializarTPersonasABB(TPersonasABB personasABB) {
    return NULL;
}

TPersonasABB deserializarTPersonasABB(TPilaPersona pilaPersonas) {
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

