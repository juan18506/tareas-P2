#include "../include/agendaLS.h"

struct rep_agendaLS {
    TEvento evento;
    rep_agendaLS *sig;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS nuevaAgenda = NULL;
    return nuevaAgenda;
}

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
    // Recorrida completa de la agenda
    while (agenda != NULL) {
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda) {
    TAgendaLS punteroAux = agenda;
    TAgendaLS otroPunteroAux = agenda;

    // Recorrida completa de la agenda
    while (punteroAux != NULL) {
        liberarTEvento(punteroAux->evento);
        punteroAux = punteroAux->sig;
        delete otroPunteroAux;
        otroPunteroAux = punteroAux;
    }

    agenda = NULL;
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return agenda == NULL;
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    TAgendaLS nuevaAgenda = crearAgendaLS();

    // Caso agenda vacia
    if (agenda == NULL) {
        return nuevaAgenda;
    }

    nuevaAgenda = new rep_agendaLS;
    TAgendaLS punteroAux = nuevaAgenda;

    while (agenda != NULL) {
        punteroAux->evento = copiarTEvento(agenda->evento);

        // Se ejecuta el else SOLO en la ultima iteracion del while
        if (agenda->sig != NULL) {
            punteroAux->sig = new rep_agendaLS;
        } else {
            punteroAux->sig = NULL;
        }


        punteroAux = punteroAux->sig;
        agenda = agenda->sig;
    }

    return nuevaAgenda;
}


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    // Recorre la agenda mientras que no encuentra el ID buscado
    while (agenda != NULL && idTEvento(agenda->evento) != id) {
        agenda = agenda->sig;
    }
    
    return agenda != NULL;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    // Recorre la agenda hasta encontrar el id buscado (en rango por PRE)
    while (idTEvento(agenda->evento) != id) {
        agenda = agenda->sig;
    }

    return agenda->evento;
}


void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    TAgendaLS punteroAux = agenda;
    TEvento eventoAux;

    // Recorre la agenda hasta encontrar el ID
    while (idTEvento(punteroAux->evento) != id) {
        punteroAux = punteroAux->sig;
    }

    posponerTEvento(punteroAux->evento, n);

    // Mueve el evento en la agenda hasta que este en la posicion correcta (bajo el critero de agregarEnAgendaLS)
    while (punteroAux->sig != NULL && compararTFechas(fechaTEvento(punteroAux->evento), fechaTEvento(punteroAux->sig->evento)) == 1) {
        eventoAux = punteroAux->evento;
        punteroAux->evento = punteroAux->sig->evento;
        punteroAux->sig->evento = eventoAux;
        punteroAux = punteroAux->sig;
    }
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    // Recorre la agenda hasta encontrar el primer evento con la fecha dada
    while (agenda != NULL && compararTFechas(fechaTEvento(agenda->evento), fecha) != 0) {
        agenda = agenda->sig;
    }

    // Imprime todos los eventos que tengan esa fecha 
    while (agenda != NULL && compararTFechas(fechaTEvento(agenda->evento), fecha) == 0) {
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    // Recorre la agenda hasta que encuentra un evento con la fecha dada
    while (agenda != NULL && compararTFechas(fechaTEvento(agenda->evento), fecha) != 0) {
        agenda = agenda->sig;
    }

    return agenda != NULL;
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

    // Recorrida en el arreglo buscando el evento con el ID dado (en rango por PRE)
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