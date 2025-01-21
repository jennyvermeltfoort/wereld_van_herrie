#ifndef __WACHTER_MAP_H
#define __WACHTER_MAP_H

#include <stdio.h>

#include "raylib.h"
#include "scherm.h"

#define CEL_MAAT_X 16
#define CEL_MAAT_Y 16
#define CEL_MAAT CEL_MAAT_X *CEL_MAAT_Y

#define MAX_POORTEN 16
#define MAP_MAAT_X 28
#define MAP_MAAT_Y 28
#define MAP_MAAT MAP_MAAT_X *MAP_MAAT_Y

typedef struct Color map_cel_t;

typedef enum : uint8_t {
    map_eigenschap_bewandelbaar = 0,
    map_eigenschap_onberijkbaar = 1,
    map_eigenschap_poort = 2,
} map_cel_eigenschap_e;

typedef enum : uint8_t {
    map_id_0 = 0,
    map_id_1 = 1,
    map_id_2 = 2,
    map_id_3 = 3,
    map_id_4 = 4,
    map_id_5 = 5,
    map_id_6 = 6,
    map_id_7 = 7,
} map_id_e;

typedef enum : uint8_t {
    map_richting_omhoog = 0,
    map_richting_rechts = 1,
    map_richting_omlaag = 2,
    map_richting_links = 3,
} map_richting_e;

typedef struct {
    map_id_e naar;
    uint8_t x;
    uint8_t y;
    map_richting_e richting;
} map_poort_t;

typedef struct {
    map_poort_t poorten[MAP_MAAT];
    uint8_t eigenschappen[MAP_MAAT];
    map_cel_t *terrein[MAP_MAAT];
} map_t;

map_t *map_alloceer(void);
void map_dealloceer(map_t *map);
void map_vrijmaken(map_t *map);
melding_e map_laad(map_t *map, map_id_e map_nr);
uint32_t map_compile(FILE *ingang, FILE*uitgang);

#endif  // __WACHTER_MAP_H
