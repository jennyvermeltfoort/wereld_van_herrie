#include "bediening.h"

void bediening_toets_lummel(bediening_data_t *data) {}

bediening_toets_functie_t toets_functies[0XFF] = {[0 ... (0XFF - 1)] = bediening_toets_lummel};

void bediening_registreer_toets(bediening_toets_e toets, bediening_toets_functie_t functie) {
    toets_functies[toets] = functie;
}

void bediening_verwerk_toets(bediening_toets_e toets, bediening_data_t *data) {
    toets_functies[toets](data);
}
