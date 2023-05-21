#include "../include/aplicaciones.h"

TPilaPersona menoresQueElResto(TPersonasLDE lista) {
    TPilaPersona pilaLista = crearTPilaPersona();
    TPilaPersona pilaResultado = crearTPilaPersona();

    if (cantidadTPersonasLDE(lista) == 0) {
        return pilaResultado;
    }

    apilarEnTPilaPersona(pilaLista, obtenerFinalDeTPersonasLDE(lista));
    eliminarFinalTPersonasLDE(lista);

    // Recorrida total de la lista
    while (cantidadTPersonasLDE(lista) > 0) {
        if (edadTPersona(cimaDeTPilaPersona(pilaLista)) > edadTPersona(obtenerFinalDeTPersonasLDE(lista))) {
            apilarEnTPilaPersona(pilaLista, obtenerFinalDeTPersonasLDE(lista));
        }

        eliminarFinalTPersonasLDE(lista);
    }

    // Da vuelta pilaLista en pilaResultado
    while (cantidadEnTPilaPersona(pilaLista) > 0) {
        apilarEnTPilaPersona(pilaResultado, cimaDeTPilaPersona(pilaLista));
        desapilarDeTPilaPersona(pilaLista);
    }

    liberarTPilaPersona(pilaLista);
    return pilaResultado;
}

bool sumaPares(nat k, TConjuntoIds c) {
    if (esVacioTConjuntoIds(c)) {
        return false;
    }   

    TConjuntoIds conjuntoMenoresQueK = crearTConjuntoIds(k);
    nat id = 1;
    bool flag = false;

    while (id < k) {
        if (perteneceTConjuntoIds(id, c)) {
            insertarTConjuntoIds(id, conjuntoMenoresQueK);
        }

        id++;
    }

    for (nat idI = 1; idI < k; idI++) {
        if (!perteneceTConjuntoIds(idI, conjuntoMenoresQueK)) {
            continue;
        }

        for (nat idJ = 1; idJ < k; idJ++) {
            if (!perteneceTConjuntoIds(idJ, conjuntoMenoresQueK)) {
                continue;
            }

            if (idI != idJ && idI + idJ == k) {
                flag = true;
            }
        }
    }
    
    liberarTConjuntoIds(conjuntoMenoresQueK);
    return flag;
}