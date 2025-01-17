#include "compiler.h"

#include <stdint.h>

#include "../map.h"
#include "bestand.h"

int main(int agc, char **argv) {
    if (agc != 3) {
        printf(
            "Usage: map_compiler <ingang_bestand> <uitgang_bestand>");
        return 1;
    }

    FILE *ingang;
    FILE *uitgang;

    if (fopen_s(&ingang, argv[1], "r") != 0) {
        printf("Het is niet gelukt om '%s' te openen.", argv[1]);
        return 1;
    }

    map_bestand_t map = {};
    uint32_t geschreven =
        bestand_lees_sector_poorten(ingang, "__start_poorten",
                                    "__eind_poorten", map.poorten) +
        bestand_lees_sector(ingang, "__start_terrein",
                            "__eind_terrein", map.terrein) +
        bestand_lees_sector(ingang, "__start_eigenschappen",
                            "__eind_eigenschappen",
                            map.eigenschappen);

    fclose(ingang);

    if (fopen_s(&uitgang, argv[2], "wb") != 0) {
        printf("Het is niet gelukt om '%s' te openen.", argv[2]);
        return 1;
    }
    bestand_schrijf_map(uitgang, &map);
    fclose(uitgang);

    printf("Klaar, error: %i, geschreven bytes: %u.\n",
           ferror(ingang), geschreven);
    printf("Van: %s.\n", argv[1]);
    printf("Naar: %s.\n", argv[2]);

    return 0;
}
