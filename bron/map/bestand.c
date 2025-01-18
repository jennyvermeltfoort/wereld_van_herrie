#include "bestand.h"

#include "../typen.h"
#include "compiler.h"

static inline bool bestand_is_nummer(char c) {
    return (47 < c && c < 58);
}

static inline melding_e bestand_lees_nummer(FILE *bestand,
                                            uint8_t *nummer) {
    melding_e melding = melding_fout;
    *nummer = 0;
    char c = fgetc(bestand);
    while (!feof(bestand) && bestand_is_nummer(c)) {
        *nummer = *nummer * 10 + (c - 48);
        melding = melding_ok;
        c = fgetc(bestand);
    }
    return melding;
}

static inline void bestand_consumeer_lijn(FILE *bestand) {
    while (!feof(bestand) && fgetc(bestand) != '\n');
}

static inline bool bestand_is_label(FILE *bestand,
                                    char label[static 1]) {
    uint8_t i = 0;
    char c;
    while (!feof(bestand) && (c = fgetc(bestand)) == label[i++] &&
           label[i] != '\0');
    return (label[i] == '\0');
}

void bestand_zoek_sector(FILE *bestand, char label[static 1]) {
    uint8_t li = 0;
    while (!feof(bestand) && label[li] != '\0') {
        char c = fgetc(bestand);
        if (c != label[li++]) {
            li = 0;
        }
    }
    bestand_consumeer_lijn(bestand);
}

uint32_t bestand_lees_sector_poorten(
    FILE *bestand, char label_begin[static 1],
    char label_eind[static 1], map_poort_t out[static MAX_POORTEN]) {

    bestand_zoek_sector(bestand, label_begin);
    for (uint32_t i = 0; i < MAX_POORTEN; i++) {
        bestand_lees_nummer(bestand, &out[i].naar);
        bestand_lees_nummer(bestand, &out[i].x);
        bestand_lees_nummer(bestand, &out[i].y);
        bestand_lees_nummer(bestand, &out[i].richting);
    }

    if (!bestand_is_label(bestand, label_eind)) {
        printf("Eind label niet correct.\n");
        return 0;
    }

    return MAX_POORTEN;
}

uint32_t bestand_lees_sector(FILE *bestand,
                             char label_begin[static 1],
                             char label_eind[static 1],
                             uint8_t out[static MAP_MAAT]) {
    const uint8_t buffer_omvang =
        MAP_MAAT_X + 1;  // einde van een lijn is een nieuwlijn
    uint32_t geschreven = 0;
    uint8_t in[buffer_omvang];
    uint8_t gelezen;

    bestand_zoek_sector(bestand, label_begin);
    do {
        gelezen = fread_s(in, buffer_omvang * sizeof(in[0]),
                          sizeof(in[0]), buffer_omvang, bestand);
        for (uint8_t y = 0; y < gelezen; y++) {
            uint8_t waarde = ascii_naar_waarde[in[y]];
            if (waarde != ONGEDEFINEERD) {
                out[geschreven++] = waarde;
            }
        }
    } while (geschreven < MAP_MAAT && gelezen != 0);

    if (!bestand_is_label(bestand, label_eind)) {
        printf("Eind label niet correct.\n");
        return 0;
    }

    return geschreven;
}

void bestand_schrijf_map(FILE *bestand, map_bestand_t *map) {
    fwrite(map, 1, sizeof(map_bestand_t), bestand);
}
