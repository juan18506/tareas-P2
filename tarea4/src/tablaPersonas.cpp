#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE* tabla;
    int cota;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas nuevaTabla = NULL;
    nuevaTabla = new rep_tablaPersonas;

    nuevaTabla->tabla = new TPersonasLDE[max];
    nuevaTabla->cota = max;

    for (int i = 0; i < max; i++) {
        nuevaTabla->tabla[i] = crearTPersonasLDE();
    }
    
    return nuevaTabla;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){
    int posicion = funcionDeDispersion(nombreTPersona(persona)) % tabla->cota;
    insertarInicioDeTPersonasLDE(tabla->tabla[posicion], persona);
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    int posicion = funcionDeDispersion(nombre) % tabla->cota;
    eliminarPersonaConNombreTPersonasLDE(tabla->tabla[posicion], nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    int posicion = funcionDeDispersion(nombre) % tabla->cota;
    bool estaPersona = estaPersonaConNombreEnTPersonasLDE(tabla->tabla[posicion], nombre);
    return estaPersona;
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    int posicion = funcionDeDispersion(nombre) % tabla->cota;
    TPersona personaBuscada = obtenerPersonaConNombreTPersonasLDE(tabla->tabla[posicion], nombre);
    return personaBuscada;
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
    for (int i = 0; i < tabla->cota; i++) {
        liberarTPersonasLDE(tabla->tabla[i]);
    }

    delete [] tabla->tabla;
    tabla->tabla = NULL;
    delete tabla;
    tabla = NULL;
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
    for (int i = 0; i < tabla->cota; i++){
        imprimirTPersonasLDE(tabla->tabla[i]);
    }
}