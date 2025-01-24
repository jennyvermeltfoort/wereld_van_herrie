#include <stdio.h>

#include "afbeelding.h"
#include "raylib.h"
#include "typen.h"

#define SPELER_TEGELKAART_LOCATIE "middelen/speler.png"

struct Image afbeelding_speler;

void afbeelding_laad(char *locatie, struct Image *afbeelding) {
    *afbeelding = LoadImage(locatie);
}

void afbeelding_dealloceer(void) { UnloadImage(afbeelding_speler); }

void afbeelding_teken(int x, int y) {
    ImageDrawRectangle(&afbeelding_speler, x, y, BITMAP_MAAT_X, BITMAP_MAAT_Y,(struct Color){0,0,0,0});
}

void afbeelding_bereidvoor(void) __attribute__((constructor(102)));
void afbeelding_bereidvoor(void) {
    afbeelding_laad(SPELER_TEGELKAART_LOCATIE, &afbeelding_speler);
}
