
#include <stdbool.h>

#include "bediening.h"
#include "map.h"
#include "scherm.h"
#include "speler.h"

melding_e scherm_start(void) {
    InitWindow(800, 450, "Wereld van Herrie");

    map_t *map = map_alloceer();
    map_laad(map, map_id_0);

    while (!WindowShouldClose()) {
        BeginDrawing();

        for (uint32_t y = 0; y < MAP_MAAT_Y; y++) {
            for (uint32_t x = 0; x < MAP_MAAT_X; x++) {
                map_cel_t *p = map->terrein[y * MAP_MAAT_X + x];
                for (uint32_t ci = 0; ci < CEL_MAAT; ci++) {
                    uint32_t ypos =
                        (ci / CEL_MAAT_X) + y * CEL_MAAT_Y;
                    uint32_t xpos =
                        (ci % CEL_MAAT_X) + x * CEL_MAAT_X;

                    if (xpos >= 800) {
                        continue;
                    }

                    if (ypos >= 450) {
                        break;
                    }

                    DrawPixel(xpos, ypos, p[ci]);
                }
            }
        }

        EndDrawing();
    }

    map_dealloceer(map);
    return melding_ok;
}
