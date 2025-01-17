#ifndef __WACHTER_MAP_H
#define __WACHTER_MAP_H

#include <stdio.h>

#include "scherm.h"

#define MAX_POORTEN 16
#define MAP_MAAT_X 28
#define MAP_MAAT_Y 28
#define MAP_MAAT MAP_MAAT_X *MAP_MAAT_Y

typedef enum : uint8_t {
    map_id_0 = 0,
    map_id_1,
    map_id_2,
    map_id_3,
    map_id_4,
    map_id_5,
    map_id_6,
    map_id_7,
} map_id_e;

typedef enum : uint8_t {
	map_richting_omhoog = 0,
	map_richting_rechts = 1,
	map_richting_omlaag = 2,
	map_richting_links = 3,
} map_richting_e;

typedef struct {
    uint8_t eigenschappen[MAP_MAAT];
    uint32_t *terrein[MAP_MAAT];
} map_t;

typedef struct {
	map_id_e naar;
	uint8_t x;
	uint8_t y;
	map_richting_e richting;
} map_poort_t;

typedef struct {
	map_poort_t poorten[MAX_POORTEN];
	uint8_t eigenschappen[MAP_MAAT];
	uint8_t terrein[MAP_MAAT];
} map_bestand_t;

map_t *map_alloceer(void);
void map_vrijmaken(map_t *map);

melding_e map_laad(map_t *map, map_id_e map_nr);

void map_vul_scherm(map_t *map, scherm_kaderdata_t *kaderdata);
void map_lees_bestand(FILE*bestand, map_bestand_t *map);

#endif  // __WACHTER_MAP_H
