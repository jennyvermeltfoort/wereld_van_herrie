#ifndef __WACHTER_BEDIENING_H
#define __WACHTER_BEDIENING_H

#include <stdint.h>

#include "raylib.h"

typedef KeyboardKey bediening_toets_e;

typedef union {
    struct {
        uint16_t herhaal;
        uint8_t ll;
        uint8_t lh;
    } data;
    uint32_t plat;
} bediening_data_t;

typedef void (*bediening_toets_functie_t)(bediening_data_t* data);
void bediening_registreer_toets(bediening_toets_e toets,
                                bediening_toets_functie_t cb);
void bediening_verwerk_toets(bediening_toets_e toets,
                             bediening_data_t* data);

#endif  // __WACHTER_BEDIENING_H
