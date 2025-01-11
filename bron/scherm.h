

#ifndef __WACHTER_SCHERM_H
#define __WACHTER_SCHERM_H

#include <windows.h>
#include <stdint.h>

#include "typen.h"

typedef struct {
    uint32_t breedte;
    uint32_t hoogte;
    uint32_t *pixels;
} scherm_kaderdata_t;

melding_e scherm_start(HINSTANCE instantie,
                     HINSTANCE instantie_vorige, LPSTR lp_cmd_line,
                     int n_cmd_show);

#endif  // __WACHTER_SCHERM_H
