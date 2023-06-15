#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char **nombres, nat n) {
    TColaDePrioridadPersona cp = crearCP(MAX_ID);

    for (nat i = 0; i < n; i++) {
        if (!perteneceATTablaPersonas(t, nombres[i])) {
            continue;
        }

        TPersona persona = obtenerPersonaDeTTablaPersonas(t, nombres[i]);
        nat id = idTPersona(persona);
        if (id <= MAX_ID && !estaEnCP(id, cp)) {
            insertarEnCP(copiarTPersona(persona), cp);
        }
    }

    while (!estaVaciaCP(cp)) {
        TPersona persona = prioritaria(cp);
        imprimirTPersona(persona);
        eliminarPrioritaria(cp);
    }

    liberarCP(cp);
}