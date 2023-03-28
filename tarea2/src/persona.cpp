#include "../include/persona.h"

struct rep_persona {
    nat id;
    nat edad;
    char nombre[100];
    TAgendaLS agenda;
};

TPersona crearTPersona(nat id, nat edad, const char nombre[100], TAgendaLS agenda) {
    TPersona nuevaPersona = NULL;
    nuevaPersona = new rep_persona;

    nuevaPersona->id = id;
    nuevaPersona->edad = edad;
    strcpy(nuevaPersona->nombre, nombre);
    nuevaPersona->agenda = agenda;

    return nuevaPersona;
}

void liberarTPersona(TPersona &persona) {
    liberarAgendaLS(persona->agenda);
    delete persona;
}

//Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona) {
    printf("Persona %d: %s, %d años\n", persona->id, persona->nombre, persona->edad);
    imprimirAgendaLS(persona->agenda);
}

nat idTPersona(TPersona persona) {
    return persona->id;
}

nat edadTPersona(TPersona persona) {
    return persona->edad;
}

char* nombreTPersona(TPersona persona) {
    return persona->nombre;
}

TAgendaLS agendaTPersona(TPersona persona) {
    return persona->agenda;
}

void agregarEventoATPersona(TPersona &persona, TEvento evento) {
    agregarEnAgendaLS(persona->agenda, evento);
}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n) {
    posponerEnAgendaLS(persona->agenda, id, n);
}

void removerEventoDeTPersona(TPersona &persona, int id) {
    removerDeAgendaLS(persona->agenda, id);
}

bool estaEnAgendaDeTPersona(TPersona persona, int id) {
    return estaEnAgendaLS(persona->agenda, id);
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id) {
    return obtenerDeAgendaLS(persona->agenda, id);
}

// TODO: Orden n²
TPersona copiarTPersona(TPersona persona) {
    return crearTPersona(persona->id, persona->edad, persona->nombre, copiarAgendaLS(persona->agenda));
}
