#include <stdint.h>

#include "map.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(
            "Usage: map_compiler <ingang_bestand> <uitgang_bestand>");
        return 1;
    }

    FILE *ingang = fopen(argv[1], "r");
    FILE *uitgang = fopen(argv[2], "wb");

    if (!ingang) {
        printf("Het is niet gelukt om '%s' te openen.", argv[1]);
        return 1;
    }

    if (!uitgang) {
        printf("Het is niet gelukt om '%s' te openen.", argv[2]);
        return 1;
    }

    uint32_t geschreven = map_compile(ingang, uitgang);

    printf("Klaar, error: %i, geschreven bytes: %u.\n",
           ferror(ingang), geschreven);
    printf("Van: %s.\n", argv[1]);
    printf("Naar: %s.\n", argv[2]);

    fclose(uitgang);
    fclose(ingang);
    return 0;
}
