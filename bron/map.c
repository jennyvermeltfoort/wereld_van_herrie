#include "map.h"

#include "entiteit.h"

// [][][]
// [][][]
// [][][]

// Wereld is een grid van 16 x 16 pixel cellen;
// Een entity bestaat uit x cellen breed en y cellen hoog? OF een
// enitity is een cell. De wereld word per entity geprint naa rhet
// scherm op volgorde van priority.

#define CEL_MAAT_X 16
#define CEL_MAAT_Y 16
#define CEL_MAAT CEL_MAAT_X *CEL_MAAT_Y

typedef uint32_t cel_t[CEL_MAAT];

typedef enum : uint8_t {
    map_cel_eigenschap_bewandelbaar = 0,
    map_cel_eigenschap_onberijkbaar = 1,
    map_cel_eigenschap_poort = 2,
} map_cel_eigenschap_e;

cel_t map_terrein_pad = {[0 ...(CEL_MAAT - 1)] = 0XFFFF00};
cel_t map_terrein_boom = {[0 ...(CEL_MAAT - 1)] = 0X008080};
cel_t map_terrein_water = {[0 ...(CEL_MAAT - 1)] = 0X8080FF};
uint32_t *terrein_vertaler[] = {
    [0] = map_terrein_pad,
    [1] = map_terrein_boom,
    [2] = map_terrein_water,
};

char *map_data_locaties[] = {
    [map_id_0] = "mappen/o/map0.data.o",
    [map_id_1] = "mappen/o/map1.data.o",
    [map_id_2] = "mappen/o/map2.data.o",
    [map_id_3] = "mappen/o/map3.data.o",
    [map_id_4] = "mappen/o/map4.data.o",
    [map_id_5] = "mappen/o/map5.data.o",
    [map_id_6] = "mappen/o/map6.data.o",
    [map_id_7] = "mappen/o/map7.data.o",
};

#define MAP_OPSLAG_MAX 16
map_t *map_opslag[map_opslag_max] = {};
uint8_t map_opslag_index = 0;

map_opslag_e map_alloceer(void) {
    if (map_storage_index >= map_opslag_max) {
        free(map_storage[0]);
        map_storage_index = 0;
    }

    map_opslag[map_opslag_index++] = malloc(sizeof(map_t));
    return map_opslag_index;
}

void map_vrijmaken(map_opslag_e index) {
    free(map_opslag[index]);
    map_opslag[index] == NULL;
    while ((index + 1) < map_opslag_max && map_opslag[++index] != NULL) {
        map_opslag[index - 1] = map_opslag[index];
    }
}

melding_e map_laad(map_opslag_e index, map_id_e map_nr) {
	map_t * map = map_opslag[index];
    map_bestand_t map_bestand = {};

    FILE *bestand = fopen(map_data_locaties[map_nr], "r");
    if (bestand == NULL) {
        return melding_fout;
    }
    fread(&map_bestand, 1, sizeof(map_bestand_t), bestand);
    fclose(bestand);

    for (uint32_t i = 0; i < MAP_MAAT; i++) {
        map->terrein[i] = terrein_vertaler[map_bestand.terrein[i]];
    }

    return melding_ok;
}

void map_vul_scherm(map_opslag_e index, scherm_kaderdata_t *kaderdata) {
	map_t * map = map_opslag[index];
    for (uint32_t y = 0; y < kaderdata->hoogte; y += CEL_MAAT_Y) {
        for (uint32_t x = 0; x < kaderdata->breedte;
             x += CEL_MAAT_X) {
            uint32_t my = y / CEL_MAAT_Y;
            uint32_t mx = x / CEL_MAAT_X;

            if (mx >= MAP_MAAT_X) {
                break;
            }

            if (my >= MAP_MAAT_Y) {
                return;
            }

            uint32_t *p = map->terrein[my * MAP_MAAT_X + mx];
            for (uint32_t ci = 0; ci < CEL_MAAT; ci++) {
                uint32_t ypos = ci / CEL_MAAT_X + y;
                uint32_t xpos = ci % CEL_MAAT_X + x;

                if (xpos >= kaderdata->breedte) {
                    continue;
                }

                if (ypos >= kaderdata->hoogte) {
                    break;
                }

                kaderdata->pixels[ypos * kaderdata->breedte + xpos] =
                    p[ci];
            }
        }
    }
}
