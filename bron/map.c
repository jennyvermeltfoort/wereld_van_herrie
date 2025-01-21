#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "entiteit.h"
#include "map.h"
#include "typen.h"

#define MAP_START_POORTEN 0x25
#define MAP_ONG 0XFF

#define MAX_POORTEN 16
#define MAP_MAAT_X 28
#define MAP_MAAT_Y 28
#define MAP_MAAT MAP_MAAT_X *MAP_MAAT_Y

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
    map_eigenschap_bewandelbaar = 0,
    map_eigenschap_onberijkbaar = 1,
    map_eigenschap_poort = 2,
} map_cel_eigenschap_e;

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
    bitmap_t *terrein[MAP_MAAT];
} map_t;

typedef struct {
    map_poort_t poorten[MAX_POORTEN];
    uint8_t eigenschappen[MAP_MAAT];
    uint8_t terrein[MAP_MAAT];
} map_bestand_t;

static const uint8_t map_deeling_waarde[] = {
    [0 ... 47] = MAP_ONG,  [58 ... 64] = MAP_ONG,
    [91 ... 96] = MAP_ONG, [123 ... 127] = MAP_ONG,
    [48] = 0x00,  // 0 -> 9
    [49] = 0x01,           [50] = 0x02,
    [51] = 0x03,           [52] = 0x04,
    [53] = 0x05,           [54] = 0x06,
    [55] = 0x07,           [56] = 0x08,
    [57] = 0x09,
    [65] = 0x0A,  // A -> Z
    [66] = 0x0B,           [67] = 0x0C,
    [68] = 0x0D,           [69] = 0x0E,
    [70] = 0x0F,           [71] = 0x10,
    [72] = 0x11,           [73] = 0x12,
    [74] = 0x13,           [75] = 0x14,
    [76] = 0x15,           [77] = 0x16,
    [78] = 0x17,           [79] = 0x18,
    [80] = 0x19,           [81] = 0x1A,
    [82] = 0x1B,           [83] = 0x1C,
    [84] = 0x1D,           [85] = 0x1E,
    [86] = 0x1F,           [87] = 0x20,
    [88] = 0x21,           [89] = 0x23,
    [90] = 0x24,
    [97] = 0x25,  // a -> z
    [98] = 0x26,           [99] = 0x27,
    [100] = 0x28,          [101] = 0x29,
    [102] = 0x2A,          [103] = 0x2B,
    [104] = 0x2C,          [105] = 0x2D,
    [106] = 0x2E,          [107] = 0x2F,
    [108] = 0x30,          [109] = 0x31,
    [110] = 0x32,          [111] = 0x33,
    [112] = 0x34,          [113] = 0x35,
    [114] = 0x36,          [115] = 0x37,
    [116] = 0x38,          [117] = 0x39,
    [118] = 0x3A,          [119] = 0x3B,
    [120] = 0x3C,          [121] = 0x3D,
    [122] = 0x3E};

bitmap_t map_terrein_pad = {
    .w = {[0 ...0XFF] = {
              .r = 100, .b = 100, .g = 150, .a = 100}}};
bitmap_t map_terrein_boom = {
    .w = {
        [0 ...0XFF] = {.r = 50, .b = 50, .g = 255, .a = 100}}};
bitmap_t map_terrein_water = {
    .w = {
        [0 ...0XFF] = {.r = 50, .b = 255, .g = 50, .a = 100}}};
bitmap_t *terrein_vertaler[] = {
    [0] = &map_terrein_pad,
    [1] = &map_terrein_boom,
    [2] = &map_terrein_water,
};

const char *map_data_locaties[] = {
    [map_id_0] = "mappen/o/map0.data.o",
    [map_id_1] = "mappen/o/map1.data.o",
    [map_id_2] = "mappen/o/map2.data.o",
    [map_id_3] = "mappen/o/map3.data.o",
    [map_id_4] = "mappen/o/map4.data.o",
    [map_id_5] = "mappen/o/map5.data.o",
    [map_id_6] = "mappen/o/map6.data.o",
    [map_id_7] = "mappen/o/map7.data.o",
};

static map_t map_kern = {};

melding_e map_laad(map_id_e map_nr) {
    map_bestand_t map_bestand = {};

    FILE *bestand = fopen(map_data_locaties[map_nr], "r");
    if (bestand == NULL) {
        return melding_fout;
    }

    fread(&map_bestand, 1, sizeof(map_bestand_t), bestand);
    fclose(bestand);

    for (uint32_t i = 0; i < MAP_MAAT; i++) {
        map_kern.terrein[i] =
            terrein_vertaler[map_bestand.terrein[i]];
    }

    return melding_ok;
}

void map_bereidvoor(void) __attribute__((constructor));
void map_bereidvoor(void) { map_laad(map_id_0); }

void map_teken(void) {
    for (uint32_t y = 0; y < MAP_MAAT_Y; y++) {
        for (uint32_t x = 0; x < MAP_MAAT_X; x++) {
            bitmap_teken(map_kern.terrein[y * MAP_MAAT_X + x],
                         x * BITMAP_MAAT_X, y * BITMAP_MAAT_Y, 800,
                         450);
        }
    }
}

static inline bool map_is_nummer(char c) {
    return (47 < c && c < 58);
}

static inline melding_e map_lees_nummer(FILE *bestand,
                                        uint8_t *nummer) {
    melding_e melding = melding_fout;
    *nummer = 0;
    char c = fgetc(bestand);
    while (!feof(bestand) && map_is_nummer(c)) {
        *nummer = *nummer * 10 + (c - 48);
        melding = melding_ok;
        c = fgetc(bestand);
    }
    return melding;
}

static inline void map_consumeer_lijn(FILE *bestand) {
    while (!feof(bestand) && fgetc(bestand) != '\n');
}

static inline bool map_is_label(FILE *bestand, char label[static 1]) {
    uint8_t i = 0;
    char c;
    while (!feof(bestand) && (c = fgetc(bestand)) == label[i++] &&
           label[i] != '\0');
    return (label[i] == '\0');
}

void map_zoek_sector(FILE *bestand, char label[static 1]) {
    uint8_t li = 0;
    while (!feof(bestand) && label[li] != '\0') {
        char c = fgetc(bestand);
        if (c != label[li++]) {
            li = 0;
        }
    }
    map_consumeer_lijn(bestand);
}

uint32_t map_lees_sector_poorten(
    FILE *bestand, char label_begin[static 1],
    char label_eind[static 1], map_poort_t out[static MAX_POORTEN]) {
    map_zoek_sector(bestand, label_begin);
    for (uint32_t i = 0; i < MAX_POORTEN; i++) {
        map_lees_nummer(bestand, &out[i].naar);
        map_lees_nummer(bestand, &out[i].x);
        map_lees_nummer(bestand, &out[i].y);
        map_lees_nummer(bestand, &out[i].richting);
    }

    if (!map_is_label(bestand, label_eind)) {
        printf("Eind label niet correct.\n");
        return 0;
    }

    return MAX_POORTEN;
}

uint32_t map_lees_sector(FILE *bestand, char label_begin[static 1],
                         char label_eind[static 1],
                         uint8_t out[static MAP_MAAT]) {
    const uint8_t buffer_omvang =
        MAP_MAAT_X + 1;  // einde van een lijn is een nieuwlijn
    uint32_t geschreven = 0;
    uint8_t in[buffer_omvang];
    uint8_t gelezen;

    map_zoek_sector(bestand, label_begin);
    do {
        gelezen = fread(in, sizeof(in[0]), buffer_omvang, bestand);
        for (uint8_t y = 0; y < gelezen; y++) {
            uint8_t waarde = map_deeling_waarde[in[y]];
            if (waarde != MAP_ONG) {
                out[geschreven++] = waarde;
            }
        }
    } while (geschreven < MAP_MAAT && gelezen != 0);

    if (!map_is_label(bestand, label_eind)) {
        printf("Eind label niet correct.\n");
        return 0;
    }

    return geschreven;
}

void map_schrijf_map(FILE *bestand, map_bestand_t *bmap) {
    fwrite(bmap, 1, sizeof(map_bestand_t), bestand);
}

uint32_t map_compile(FILE *ingang, FILE *uitgang) {
    map_bestand_t bmap = {};
    uint32_t geschreven =
        map_lees_sector_poorten(ingang, "__start_poorten",
                                "__eind_poorten", bmap.poorten) +
        map_lees_sector(ingang, "__start_terrein", "__eind_terrein",
                        bmap.terrein) +
        map_lees_sector(ingang, "__start_eigenschappen",
                        "__eind_eigenschappen", bmap.eigenschappen);
    map_schrijf_map(uitgang, &bmap);
    return geschreven;
}
