#include "../include/persona.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_persona {

};

TPersona crearTPersona(nat id, nat edad, const char nombre[100], TAgendaLS agenda) {
    return NULL;
}

void liberarTPersona(TPersona &persona) {

}

//Imprime a la persona utilizando printf e imprimeAgendaLS
void imprimirTPersona(TPersona persona) {

}

nat idTPersona(TPersona persona) {
    return 0;
}

nat edadTPersona(TPersona persona) {
    return 0;
}

char* nombreTPersona(TPersona persona) {
    return NULL;
}

TAgendaLS agendaTPersona(TPersona persona) {
    return NULL;
}

void agregarEventoATPersona(TPersona &persona, TEvento evento) {

}

void posponerEventoEnTPersona(TPersona &persona, int id, nat n) {

}

void removerEventoDeTPersona(TPersona &persona, int id) {

}

bool estaEnAgendaDeTPersona(TPersona persona, int id) {
    return false;
}

TEvento obtenerDeAgendaDeTPersona(TPersona persona, int id) {
    return NULL;
}

TPersona copiarTPersona(TPersona persona) {
    return NULL;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoDeTPersona(TPersona persona){
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
