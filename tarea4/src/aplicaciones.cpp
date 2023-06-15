#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"

void listarEnOrden(TTablaPersonas t, char **nombres, nat n) {
    TColaDePrioridadPersona cp = crearCP(MAX_ID);

    // Recorrida total del arreglo nombres
    for (nat i = 0; i < n; i++) {
        // Caso nombre no pertenece a la tabla
        if (!perteneceATTablaPersonas(t, nombres[i])) {
            continue;
        }

        TPersona persona = obtenerPersonaDeTTablaPersonas(t, nombres[i]);
        nat id = idTPersona(persona);
        if (id <= MAX_ID && !estaEnCP(id, cp)) {
            insertarEnCP(copiarTPersona(persona), cp);
        }
    }

    // Imprime las personas de la cp hasta vaciarla
    while (!estaVaciaCP(cp)) {
        TPersona persona = prioritaria(cp);
        imprimirTPersona(persona);
        eliminarPrioritaria(cp);
    }

    liberarCP(cp);
}