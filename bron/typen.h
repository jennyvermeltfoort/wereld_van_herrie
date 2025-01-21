#ifndef __WACHTER_TYPEN_H
#define __WACHTER_TYPEN_H

#include <stdint.h>

#include "raylib.h"

#define BITMAP_MAAT_X 16
#define BITMAP_MAAT_Y 16
#define BITMAP_MAAT BITMAP_MAAT_X *BITMAP_MAAT_Y
typedef struct Color pixel_t;
typedef struct { 
    pixel_t w[BITMAP_MAAT];
} bitmap_t;

[[maybe_unused]] static void bitmap_teken(bitmap_t *bitmap, uint32_t x, uint32_t y, uint32_t xlimiet, uint32_t ylimiet) {
    for (uint32_t i = 0; i < BITMAP_MAAT; i++) {
        uint32_t xp = (i % BITMAP_MAAT_X) + x;
        uint32_t yp = (i / BITMAP_MAAT_X) + y;
        if (xp >= xlimiet) {
            continue;
        }
        if (yp >= ylimiet) {
            break;
        }
        DrawPixel(xp, yp, bitmap->w[i]);
    }
}

typedef enum {
    melding_ok = 0,
    melding_fout,
} melding_e;

#endif  // __WACHTER_TYPEN_H
