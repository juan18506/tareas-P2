#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 1 //////
///////////////////////////////////

struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    nuevaFecha = new rep_fecha;

    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;

    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha) {
    printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
}

// Función para obtener la cantidad de días de un mes en un año dado
nat diasMes(nat mes, nat anio) {
    nat dias; 
    bool esBisiesto;

    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            dias = 31;
            break;
            
        case 4: case 6: case 9: case 11:
            dias = 30;
            break;

        case 2:
            esBisiesto = ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0));
            if (esBisiesto) {
                dias = 29;
            } else {
                dias = 28;
            }
            break;
        
        default:
            printf("Valor no valido\n");
            dias = 0;
            break;
        }

    return dias;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;

    while(fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;

        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    bool sonIguales = (fecha1->anio == fecha2->anio) && (fecha1->mes == fecha2->mes) && (fecha1->dia == fecha2->dia);
    bool f1esMayor = (fecha1->anio > fecha2->anio) || (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) || (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia);

    if (f1esMayor) {
        res++;
    } else if (!sonIguales) {
        res--;
    }

    return res;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
    return crearTFecha(fecha->dia, fecha->mes, fecha->anio);
}
