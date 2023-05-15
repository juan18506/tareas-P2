#include "../include/aplicaciones.h"

TPilaPersona menoresQueElResto(TPersonasLDE lista) {
    TPilaPersona pilaLista = crearTPilaPersona();
    TPilaPersona pilaResultado = crearTPilaPersona();

    if (cantidadTPersonasLDE(lista) == 0) {
        return pilaResultado;
    }

    apilarEnTPilaPersona(pilaLista, obtenerFinalDeTPersonasLDE(lista));
    eliminarFinalTPersonasLDE(lista);

    while (cantidadTPersonasLDE(lista) > 0) {
        if (edadTPersona(cimaDeTPilaPersona(pilaLista)) > edadTPersona(obtenerFinalDeTPersonasLDE(lista))) {
            apilarEnTPilaPersona(pilaLista, obtenerFinalDeTPersonasLDE(lista));
        }

        eliminarFinalTPersonasLDE(lista);
    }

    while (cantidadEnTPilaPersona(pilaLista) > 0) {
        apilarEnTPilaPersona(pilaResultado, cimaDeTPilaPersona(pilaLista));
        desapilarDeTPilaPersona(pilaLista);
    }

    liberarTPilaPersona(pilaLista);
    return pilaResultado;
}

bool sumaPares(nat k, TConjuntoIds c) {
    return false;
}