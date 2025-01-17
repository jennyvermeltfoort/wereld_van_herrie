
#ifndef __WACHTER_BESTAND_H
#define __WACHTER_BESTAND_H

#include <stdio.h>
#include <stdint.h>
#include "../map.h"

uint32_t bestand_lees_sector_poorten(FILE* bestand,
                             char label_begin[static 1],
                             char label_eind[static 1],
                             map_poort_t out[static MAX_POORTEN]);
uint32_t bestand_lees_sector(FILE *bestand, char label_begin[static 1],
                             char label_eind[static 1],
                             uint8_t out[static MAP_MAAT]) ;
void bestand_schrijf_map(FILE*bestand, map_bestand_t *map);

#endif // __WACHTER_BESTAND_H
