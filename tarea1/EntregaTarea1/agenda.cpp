#include "../include/agenda.h"

struct rep_agenda {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TEvento agenda[MAX_EVENTOS];
    nat tope;
    /****** Fin de parte Parte 5.1 *****/
};

TAgenda crearTAgenda() {
    TAgenda nuevaAgenda = NULL;
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    nuevaAgenda = new rep_agenda;
    nuevaAgenda->tope = 0;
    /****** Fin de parte Parte 5.2 *****/
    return nuevaAgenda;
}

void agregarEnAgenda(TAgenda &agenda, TEvento evento) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    nat i = agenda->tope;
    if (i < MAX_EVENTOS) {
        agenda->agenda[i] = evento;
        while ((i > 0) && (compararTFechas(fechaTEvento(agenda->agenda[i - 1]), fechaTEvento(agenda->agenda[i])) == 1 || compararTFechas(fechaTEvento(agenda->agenda[i - 1]), fechaTEvento(agenda->agenda[i])) == 0)) {
            agenda->agenda[i] = agenda->agenda[i - 1];
            agenda->agenda[i - 1] = evento;
            i--;
        }
        agenda->tope++;
    }
    /****** Fin de parte Parte 5.2 *****/
}

void liberarTAgenda(TAgenda &agenda) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++) {
        liberarTEvento(agenda->agenda[i]);
    }
    delete agenda;
    agenda = NULL;
    /****** Fin de parte Parte 5.2 *****/
}

void imprimirTAgenda(TAgenda agenda) {
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for (nat i = 0; i < agenda->tope; i++) {
        imprimirTEvento(agenda->agenda[i]);
    }
    /****** Fin de parte Parte 5.2 *****/
}

bool estaEnAgenda(TAgenda agenda, int id) {
    bool res = false;
    /************ Parte 5.4 ************/
    /*Escriba el código a continuación */
    nat i = 0;
    while (i < agenda->tope && idTEvento(agenda->agenda[i]) != id) {
        i++;
    }
    res = i < agenda->tope;
    /****** Fin de parte Parte 5.4 *****/
    return res;
}

TEvento obtenerDeAgenda(TAgenda agenda, int id) {
    TEvento res = NULL;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    nat i = 0;
    while (idTEvento(agenda->agenda[i]) != id) {
        i++;
    }
    res = agenda->agenda[i];
    /****** Fin de parte Parte 5.5 *****/
    return res;
}

void posponerEnAgenda(TAgenda &agenda, int id, nat n) {
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    nat i = 0;
    while (idTEvento(agenda->agenda[i]) != id) {
        i++;
    }
    posponerTEvento(agenda->agenda[i], n);
    TEvento auxEvento;
    while (i < (agenda->tope - 1) && compararTFechas(fechaTEvento(agenda->agenda[i]), fechaTEvento(agenda->agenda[i + 1])) == 1) {
        auxEvento = agenda->agenda[i];
        agenda->agenda[i] = agenda->agenda[i + 1];
        agenda->agenda[i + 1] = auxEvento; 
        i++;
    }
    /****** Fin de parte Parte 5.5 *****/
}

void imprimirEventosFecha(TAgenda agenda, TFecha fecha) {
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    nat i = 0;
    while (i < agenda->tope && compararTFechas(fechaTEvento(agenda->agenda[i]), fecha) != 0) {
        i++;
    }
    while (i < agenda->tope && compararTFechas(fechaTEvento(agenda->agenda[i]), fecha) == 0) {
        imprimirTEvento(agenda->agenda[i]);
        i++;
    }
    /****** Fin de parte Parte 5.7 *****/
}

bool hayEventosFecha(TAgenda agenda, TFecha fecha) {
    bool res = false;
    /************ Parte 5.7 ************/
    /*Escriba el código a continuación */
    /*La función debe ejecutar una versión */
    /*Iterativa del algoritmo de búsqueda  */
    /*binaria.                              */
    int inf = 0;
    int sup = agenda->tope - 1;
    int mitad;
    while (inf <= sup && !res) {
        mitad = (inf + sup) / 2;
        if (compararTFechas(fechaTEvento(agenda->agenda[mitad]), fecha) == 0) {
            res = true;
        }
        if (compararTFechas(fechaTEvento(agenda->agenda[mitad]), fecha) == 1) {
            sup = mitad - 1;
        }
        if (compararTFechas(fechaTEvento(agenda->agenda[mitad]), fecha) == -1) {
            inf = mitad + 1;
        }
    }

    /****** Fin de parte Parte 5.7 *****/
    return res;
}

void removerDeAgenda(TAgenda &agenda, int id) {
    /************ Parte 5.8 ************/
    /*Escriba el código a continuación */
    nat i = 0;
    while (idTEvento(agenda->agenda[i]) != id) {
        i++;
    }
    liberarTEvento(agenda->agenda[i]);
    while (i < agenda->tope) {
        agenda->agenda[i] = agenda->agenda[i + 1];
        i++;
    }
    agenda->agenda[i - 1] = NULL;
    agenda->tope--;
    /****** Fin de parte Parte 5.8 *****/
}
