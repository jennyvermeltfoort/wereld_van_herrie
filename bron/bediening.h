#ifndef __WACHTER_BEDIENING_H
#define __WACHTER_BEDIENING_H

#include <stdint.h>

#include "raylib.h"

typedef KeyboardKey bediening_toets_e;

typedef void (*bediening_toets_functie_t)(void);
void bediening_registreer_toets(bediening_toets_e toets,
                                bediening_toets_functie_t cb);
void bediening_verwerk_toets(bediening_toets_e toets);

#endif  // __WACHTER_BEDIENING_H
