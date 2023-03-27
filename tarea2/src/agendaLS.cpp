#include "../include/agendaLS.h"

struct rep_agendaLS {
    TEvento evento;
    rep_agendaLS *sig;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS nuevaAgenda = NULL;
    return nuevaAgenda;
}

// TODO: chequear si se podria hacer mejor
void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    // Puntero al nuevo evento en forma de lista
    TAgendaLS nuevoEvento = new rep_agendaLS;
    nuevoEvento->evento = evento;
    nuevoEvento->sig = NULL;

    // Caso agenda vacia
    if (agenda == NULL) {
        agenda = nuevoEvento;
        return;
    }

    // Caso agenda con 1 evento
    if (agenda->sig == NULL) {
        if (compararTFechas(fechaTEvento(evento), fechaTEvento(agenda->evento)) == 1) {
            agenda->sig = nuevoEvento;
        } else {
            nuevoEvento->sig = agenda;
            agenda = nuevoEvento;
        }

        return;
    }

    TAgendaLS anteriorAux = agenda;
    TAgendaLS punteroAux = agenda->sig;

    // Caso nuevoEvento debe ser ubicado en el 1er lugar de la agenda
    if (compararTFechas(fechaTEvento(evento), fechaTEvento(anteriorAux->evento)) != 1) {
        nuevoEvento->sig = anteriorAux;
        agenda = nuevoEvento;
        return;
    }

    // Recorrida en la lista 
    while (punteroAux != NULL && compararTFechas(fechaTEvento(evento), fechaTEvento(punteroAux->evento)) == 1) {
        punteroAux = punteroAux->sig;
        anteriorAux = anteriorAux->sig;
    }

    // Caso fecha(nuevoEvento) > fecha(evento) para todo evento de agenda
    if (punteroAux == NULL) {
        anteriorAux->sig = nuevoEvento;
        return;
    }

    // Casos en que fecha(nuevoEvento) <= fecha(evento) para algun evento de agenda
    if (compararTFechas(fechaTEvento(evento), fechaTEvento(punteroAux->evento)) == 1) {
        nuevoEvento->sig = punteroAux->sig;
        punteroAux->sig = nuevoEvento;
    } else {
        nuevoEvento->sig = anteriorAux->sig;
        anteriorAux->sig = nuevoEvento;
    }
}


void imprimirAgendaLS(TAgendaLS agenda) {
    TAgendaLS punteroAux = agenda;

    // Recorrida completa de la agenda
    while (punteroAux != NULL) {
        imprimirTEvento(punteroAux->evento);
        punteroAux = punteroAux->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda) {
    TAgendaLS punteroAux = agenda;
    TAgendaLS otroPunteroAux = agenda;

    // Recorrida en la agenda
    while (punteroAux != NULL) {
        liberarTEvento(punteroAux->evento);
        punteroAux = punteroAux->sig;
        delete otroPunteroAux;
        otroPunteroAux = punteroAux;
    }
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return agenda == NULL;
}

// TODO: revisar tiempo de ejecucion
TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    TAgendaLS punteroAux = agenda;
    TAgendaLS nuevaAgenda = crearAgendaLS();

    while (punteroAux != NULL) {
        agregarEnAgendaLS(nuevaAgenda, copiarTEvento(punteroAux->evento));
        punteroAux = punteroAux->sig;
    }

    return nuevaAgenda;
}


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    TAgendaLS punteroAux = agenda;

    // Recorre la agenda mientras que no encuentra el ID buscado
    while (punteroAux != NULL && idTEvento(punteroAux->evento) != id) {
        punteroAux = punteroAux->sig;
    }
    
    return punteroAux != NULL;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    TAgendaLS punteroAux = agenda;

    while (idTEvento(punteroAux->evento) != id) {
        punteroAux = punteroAux->sig;
    }

    return punteroAux->evento;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    TAgendaLS punteroAux = agenda;
    TEvento eventoAux;

    // Recorre la agenda hasta encontrar el ID
    while (idTEvento(punteroAux->evento) != id) {
        punteroAux = punteroAux->sig;
    }

    posponerTEvento(punteroAux->evento, n);

    // Mueve el evento en la agenda hasta que este en la posicion correcta (segun agregarEnAgendaLS)
    while (punteroAux->sig != NULL && compararTFechas(fechaTEvento(punteroAux->evento), fechaTEvento(punteroAux->sig->evento)) == 1) {
        eventoAux = punteroAux->evento;
        punteroAux->evento = punteroAux->sig->evento;
        punteroAux->sig->evento = eventoAux;
        punteroAux = punteroAux->sig;
    }
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS punteroAux = agenda;

    // Recorre la agenda hasta encontrar el primer evento con la fecha dada
    while (punteroAux != NULL && compararTFechas(fechaTEvento(punteroAux->evento), fecha) != 0) {
        punteroAux = punteroAux->sig;
    }

    // Imprime todos los eventos que tengan esa fecha 
    while (punteroAux != NULL && compararTFechas(fechaTEvento(punteroAux->evento), fecha) == 0) {
        imprimirTEvento(punteroAux->evento);
        punteroAux = punteroAux->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS punteroAux = agenda;

    // Recorre la agenda hasta que encuentra un evento con la fecha dada
    while (punteroAux != NULL && compararTFechas(fechaTEvento(punteroAux->evento), fecha) != 0) {
        punteroAux = punteroAux->sig;
    }

    return punteroAux != NULL;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    TAgendaLS punteroAux = agenda->sig;
    TAgendaLS punteroAnteriorAux = agenda;

    // Caso en que la agenda tiene un solo elemento
    if (agenda->sig == NULL) {
        liberarTEvento(agenda->evento);
        delete agenda;
        agenda = NULL;
        return;
    }

    // Caso el evento a remover es el 1ero en la agenda
    if (idTEvento(agenda->evento) == id) {
        liberarTEvento(agenda->evento);
        delete agenda;
        agenda = punteroAux;
        return;
    }

    // Recorrida en el arreglo buscando el evento con el ID dado
    while (idTEvento(punteroAux->evento) != id) {
        punteroAnteriorAux = punteroAnteriorAux->sig;
        punteroAux = punteroAux->sig;
    }

    // Se elimina el evento 
    liberarTEvento(punteroAux->evento);
    punteroAux = punteroAux->sig;
    delete punteroAnteriorAux->sig;
    punteroAnteriorAux->sig = punteroAux;
}