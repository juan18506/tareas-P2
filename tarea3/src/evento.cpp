#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////

struct rep_evento {
    int id;
    char descripcion[MAX_DESCRIPCION];
    TFecha fecha;
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;
    nuevoEvento = new rep_evento;

    nuevoEvento->id = id;
    strcpy(nuevoEvento->descripcion, descripcion);
    nuevoEvento->fecha = fecha;

    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
    printf("Evento %d: %s\nFecha: ", evento->id, evento->descripcion);
    imprimirTFecha(evento->fecha);
}

void liberarTEvento(TEvento &evento) {
    liberarTFecha(evento->fecha);
    delete evento;
    evento = NULL;
}

int idTEvento(TEvento evento) {
    int res = 0;
    res = evento->id;
    return res;
}

TFecha fechaTEvento(TEvento evento) {
    TFecha fecha = NULL;
    fecha = evento->fecha;
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    if (dias < 0) return;
    aumentarTFecha(evento->fecha, dias);
}

// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento) {
    return crearTEvento(evento->id, evento->descripcion, copiarTFecha(evento->fecha));
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
/////////////////////////////////
