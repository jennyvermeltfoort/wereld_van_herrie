#ifndef __WACHTER_ENTITEIT_H
#define __WACHTER_ENTITEIT_H

#include <stdint.h>

#include "typen.h"

typedef enum : uint8_t {
    entiteit_richting_noord = 0,
    entiteit_richting_oost = 1,
    entiteit_richting_zuid = 2,
    entiteit_richting_west = 3,
} entiteit_richting_e;

typedef enum : uint8_t {
    entiteit_rang_l0 = 0,  // teken eerst
    entiteit_rang_l1 = 1,
    entiteit_rang_l2 = 2,
    entiteit_rang_nul = 3,
} entiteit_rang_e;

typedef struct {
    uint16_t x;
    uint16_t y;
    entiteit_richting_e richting;
    bitmap_t bitmap;
} entiteit_t;

entiteit_t* entiteit_maak(entiteit_rang_e rang);
void entiteit_zuiver(void);
void entiteit_teken(void);

#define ENTITEIT_MAAK(_entiteit, _rang)                                \
    entiteit_t* _entiteit;                                             \
    static void __maak_##_entiteit(void) __attribute__((constructor(101))); \
    static void __maak_##_entiteit(void) { _entiteit = entiteit_maak(_rang); }

#endif  //  __WACHTER_ENTITEIT_H
