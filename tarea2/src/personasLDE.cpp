#include "../include/personasLDE.h"

struct rep_nodosLDE {
    rep_nodosLDE *ant;
    TPersona persona;
    rep_nodosLDE *sig;
};

struct rep_personasLDE {
    rep_nodosLDE *inicio;
    rep_nodosLDE *final;
    nat cantidad;
};

TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE nuevaLista = new rep_personasLDE;
    nuevaLista->inicio = NULL;
    nuevaLista->final = NULL;
    nuevaLista->cantidad = 0;

    return nuevaLista;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    rep_nodosLDE *personaAux = NULL;
    rep_nodosLDE *punteroAux = personas->inicio;
    nat contador = 0;

    if (personas->inicio == NULL) {
        personas->inicio = new rep_nodosLDE;
        personas->inicio->ant = NULL;
        personas->inicio->sig = NULL;
        personas->inicio->persona = persona;
        personas->final = personas->inicio;
        personas->cantidad++;
        return;
    } else if (pos == 1) {
        personaAux = new rep_nodosLDE;
        personaAux->ant = NULL;
        personaAux->persona = persona;
        personaAux->sig = personas->inicio;
        personas->inicio->ant = personaAux;
        personas->inicio = personaAux;
        personas->cantidad++;
        return;
    }

    while (punteroAux->sig != NULL && contador < pos - 2) {
        punteroAux = punteroAux->sig;
        contador++;
    }

    // Caso donde la persona se inserta al final de la lista
    if (punteroAux->sig == NULL) {
        personaAux = new rep_nodosLDE;
        personaAux->ant = punteroAux;
        personaAux->persona = persona;
        personaAux->sig = NULL;
        punteroAux->sig = personaAux;
        personas->final = personaAux;
        personas->cantidad++;
        return;
    }

    personaAux = new rep_nodosLDE;
    personaAux->ant = punteroAux;
    personaAux->persona = persona;
    personaAux->sig = punteroAux->sig;
    punteroAux->sig->ant = personaAux;
    punteroAux->sig = personaAux;
    personas->cantidad++;
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE){
    rep_nodosLDE *punteroAux = personasLDE->inicio;
    rep_nodosLDE *otroPunteroAux = personasLDE->inicio;

    while (punteroAux != NULL) {
        liberarTPersona(punteroAux->persona);
        punteroAux = punteroAux->sig;
        delete otroPunteroAux;
        otroPunteroAux = punteroAux;
    }

    delete personasLDE;
    personasLDE = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    rep_nodosLDE *punteroAux = personas->inicio;

    while (punteroAux != NULL) {
        imprimirTPersona(punteroAux->persona);
        punteroAux = punteroAux->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    return personas->cantidad;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas->inicio == NULL) {
        return;
    }

    if (personas->inicio->sig == NULL) {
        liberarTPersona(personas->inicio->persona);
        delete personas->inicio;
        personas->inicio = NULL;
        personas->final = NULL;
        personas->cantidad--;
        return;
    }

    rep_nodosLDE *punteroAux = personas->inicio->sig;
    liberarTPersona(personas->inicio->persona);
    delete personas->inicio;
    personas->inicio = punteroAux;
    punteroAux->ant = NULL;
    personas->cantidad--;
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if (personas->inicio == NULL) {
        return;
    }

    if (personas->inicio->sig == NULL) {
        liberarTPersona(personas->inicio->persona);
        delete personas->inicio;
        personas->inicio = NULL;
        personas->final = NULL;
        personas->cantidad--;
        return;
    }

    rep_nodosLDE *punteroAux = personas->final->ant;
    liberarTPersona(personas->final->persona);
    delete personas->final;
    personas->final = punteroAux;
    punteroAux->sig = NULL;
    personas->cantidad--;
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    rep_nodosLDE *punteroAux = personas->inicio;

    while (punteroAux != NULL && idTPersona(punteroAux->persona) != id) {
        punteroAux = punteroAux->sig;
    }
    
    return punteroAux != NULL;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    rep_nodosLDE *punteroAux = personas->inicio;

    while (idTPersona(punteroAux->persona) != id) {
        punteroAux = punteroAux->sig;
    }

    return punteroAux->persona;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    TPersonasLDE personas = personas1;
    
    if (personas2->inicio == NULL) {
        personas->cantidad += personas2->cantidad;
        personas2->inicio = NULL;
        personas2->final = NULL;
        delete personas2;
        return personas;
    }

    if (personas1->inicio == NULL) {
        personas = personas2;
        personas->cantidad += personas1->cantidad;
        personas1->inicio = NULL;
        personas1->final = NULL;
        delete personas1;
        return personas;
    }

    personas->final->sig = personas2->inicio;
    personas2->inicio->ant = personas->final;
    personas->final = personas2->final;
    personas->cantidad += personas2->cantidad;
    personas2->inicio = NULL;
    personas2->final = NULL;
    delete personas2;
    return personas;
}