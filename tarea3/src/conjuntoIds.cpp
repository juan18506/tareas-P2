#include "../include/conjuntoIds.h"

struct rep_conjuntoIds{
  bool * setIds;
	nat cantidad;
	nat cantidadMaxima;
};

TConjuntoIds crearTConjuntoIds(nat cantMax){
	TConjuntoIds conjuntoIds = NULL;
	conjuntoIds = new rep_conjuntoIds;

	conjuntoIds->setIds = new bool [cantMax];
	conjuntoIds->cantidadMaxima = cantMax;
	conjuntoIds->cantidad = 0;

	for (nat id = 1; id <= cantMax; id++) {
		conjuntoIds->setIds[id - 1] = false;	
	}
	
	return conjuntoIds;
};

bool esVacioTConjuntoIds(TConjuntoIds c){
	return c->cantidad == 0;
};

void insertarTConjuntoIds(nat id, TConjuntoIds &c){
	if (0 < id && id <= c->cantidadMaxima && !c->setIds[id - 1]) {
		c->setIds[id - 1] = true;
		c->cantidad++;
	}
}; 

void borrarTConjuntoIds(nat id, TConjuntoIds &c){
  if (0 < id && id <= c->cantidadMaxima && c->setIds[id - 1]) {
		c->setIds[id - 1] = false;
		c->cantidad--;
	}
};

bool perteneceTConjuntoIds(nat id, TConjuntoIds c){
	return 0 < id && id <= c->cantidadMaxima && c->setIds[id - 1];
};

nat cardinalTConjuntoIds(TConjuntoIds c){
	return c->cantidad;
};

nat cantMaxTConjuntoIds(TConjuntoIds c){
	return c->cantidadMaxima;
};

void imprimirTConjuntoIds(TConjuntoIds c){
  for (nat id = 1; id <= c->cantidadMaxima; id++) {
		if (c->setIds[id - 1]) {
			printf("%u ", id);
		}
	};
	
	printf("\n");
};

void liberarTConjuntoIds(TConjuntoIds &c){
  delete [] c->setIds;
	delete c;
	c = NULL;
};




TConjuntoIds unionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
	TConjuntoIds unionIds = crearTConjuntoIds(c1->cantidadMaxima + c2->cantidadMaxima);

	for (nat id = 1; id <= unionIds->cantidadMaxima; id++) {
		if (perteneceTConjuntoIds(id, c1) || perteneceTConjuntoIds(id, c2)) {
			insertarTConjuntoIds(id, unionIds);
		}
	}

	return unionIds;
};

TConjuntoIds interseccionTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
	TConjuntoIds interseccionIds = crearTConjuntoIds(c1->cantidadMaxima);

	for (nat id = 1; id <= interseccionIds->cantidadMaxima; id++) {
		if (perteneceTConjuntoIds(id, c1) && perteneceTConjuntoIds(id, c2)) {
			insertarTConjuntoIds(id, interseccionIds);
		}
	}

	return interseccionIds;
};

TConjuntoIds diferenciaTConjuntoIds(TConjuntoIds c1, TConjuntoIds c2){
	TConjuntoIds diferenciaIds = crearTConjuntoIds(c1->cantidadMaxima);

	for (nat id = 1; id <= diferenciaIds->cantidadMaxima; id++) {
		if (perteneceTConjuntoIds(id, c1) && !perteneceTConjuntoIds(id, c2)) {
			insertarTConjuntoIds(id, diferenciaIds);
		}
	}

	return diferenciaIds;
};
