#include <stdio.h>

#include "typen.h"

melding_e afbeelding_laad(char *bestand) {
    FILE *b = fopen(bestand, "r");

    if (b == NULL) {
        return melding_fout;
    }

    uint64_t handtekening;
    fread(&handtekening, sizeof(handtekening), 1, b);
    if (handtekening != 0X89504E470D0A1A0A) {
        return melding_fout;
    }

    struct {
        uint64_t lengte;
        uint64_t type;
    } klomphoofd;
    fread(&klomphoofd, 4, 2, b);

    fclose(b);
    return melding_fout;
}
