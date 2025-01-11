#include "entiteit.h"


entiteit_lijst_t *lijsten[entiteit_rang_nul] = {};


void entiteit_lijst_init(entiteit_lijst_t *lijst, entiteit_rang_e rang) {
	lijsten[rang] = lijst;
}

entiteit_lijst_t * entiteit_rang_lijst_neem(entiteit_rang_e rang) {
	return lijsten[rang];
}
