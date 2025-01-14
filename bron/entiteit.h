#ifndef __WACHTER_ENTITEIT_H
#define __WACHTER_ENTITEIT_H

#include <stdint.h>

typedef enum {
    ent_richt_noord,
    ent_richt_oost,
    ent_richt_zuid,
    ent_richt_west,
} entiteit_richting_e;

typedef struct {
    uint16_t x;
    uint16_t y;
    entiteit_richting_e richt;
} entiteit_t;

typedef struct {
    entiteit_t *entiteiten;
    uint8_t aantal;
    uint8_t omvang;
} entiteit_lijst_t;

typedef enum {
    entiteit_rang_l0,  // teken eerst
    entiteit_rang_l1,
    entiteit_rang_l2,
    entiteit_rang_nul,
} entiteit_rang_e;

void entiteit_loop(entiteit_t *ent, entiteit_richting_e richt);

#endif  //  __WACHTER_ENTITEIT_H
