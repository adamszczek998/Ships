#include "data_structures.h"


int main() {

	data_structures::List<int> nowaLista;
	nowaLista.add(5);
	nowaLista.add(12);
	nowaLista.add(8);
	data_structures::List<int> kopia = nowaLista;
	

	return 0;
}