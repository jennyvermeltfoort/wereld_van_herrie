#include "raylib.h"

#include "entiteit.h"

#define ENTITEIT_MAX 0XFF

typedef struct {
    entiteit_t entiteiten[ENTITEIT_MAX];
    uint32_t index;
} entiteit_lijst_t;

entiteit_lijst_t entiteit_lijst_l0 = {};
entiteit_lijst_t entiteit_lijst_l1 = {};
entiteit_lijst_t entiteit_lijst_l2 = {};
entiteit_lijst_t *lijsten[] = {
    [entiteit_rang_l0] = &entiteit_lijst_l0,
    [entiteit_rang_l1] = &entiteit_lijst_l1,
    [entiteit_rang_l2] = &entiteit_lijst_l2,
};

entiteit_t *entiteit_maak(entiteit_rang_e rang) {
    entiteit_lijst_t *lijst = lijsten[rang];
    return &lijst->entiteiten[lijst->index++];
}

void entiteit_zuiver(void) {
    for (uint32_t r = 0; r < entiteit_rang_nul; r++) {
        lijsten[r]->index = 0;
    }
}

void entiteit_teken(void) {
    for (uint32_t r = 0; r < entiteit_rang_nul; r++) {
        entiteit_lijst_t *lijst = lijsten[r];
        for (uint32_t i = 0; i < lijst->index; i++) {
            entiteit_t *entiteit = &lijst->entiteiten[i];
            bitmap_teken(entiteit->bitmap, entiteit->x, entiteit->y,
                         800, 450);
        }
    }
}
