#include "bediening.h"

void bediening_toets_lummel(void) {return;}

bediening_toets_functie_t toets_functies[0XFFFF] = {
    [0 ...(0XFFFF - 1)] = bediening_toets_lummel};

void bediening_registreer_toets(bediening_toets_e toets,
                                bediening_toets_functie_t functie) {
    toets_functies[toets] = functie;
}

void bediening_verwerk_toets(bediening_toets_e toets) {
    toets_functies[toets]();
}

