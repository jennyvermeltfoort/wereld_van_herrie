#include <stddef.h>

#include "bediening.h"
#include "entiteit.h"
#include "speler.h"

ENTITEIT_MAAK(speler, entiteit_rang_l0);

static bitmap_t speler_bitmap = {
    .w = {[0 ...0XFF] = {
              .r = 255, .b = 255, .g = 255, .a = 255}}};

void speler_verplaats_omhoog(void) {
    speler->y -= 5;
}

void speler_verplaats_omlaag(void) {
    speler->y += 5;
}

void speler_verplaats_links(void) {
    speler->x -= 5;
}

void speler_verplaats_rechts(void) {
    speler->x += 5;
}

void speler_bereidvoor(void) __attribute__((constructor));
void speler_bereidvoor(void) {
    speler->bitmap = &speler_bitmap;
    bediening_registreer_toets(KEY_UP,
                               speler_verplaats_omhoog);
    bediening_registreer_toets(KEY_DOWN,
                               speler_verplaats_omlaag);
    bediening_registreer_toets(KEY_LEFT,
                               speler_verplaats_links);
    bediening_registreer_toets(KEY_RIGHT,
                               speler_verplaats_rechts);
    bediening_registreer_toets(KEY_W,
                               speler_verplaats_omhoog);
    bediening_registreer_toets(KEY_S,
                               speler_verplaats_omlaag);
    bediening_registreer_toets(KEY_A,
                               speler_verplaats_links);
    bediening_registreer_toets(KEY_D,
                               speler_verplaats_rechts);
}
