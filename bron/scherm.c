
#include <stdbool.h>

#include "bediening.h"
#include "entiteit.h"
#include "map.h"
#include "scherm.h"
#include "speler.h"

melding_e scherm_start(void) {
    InitWindow(800, 450, "Wereld van Herrie");

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) bediening_verwerk_toets(KEY_UP);
        if (IsKeyDown(KEY_S)) bediening_verwerk_toets(KEY_DOWN);
        if (IsKeyDown(KEY_A)) bediening_verwerk_toets(KEY_LEFT);
        if (IsKeyDown(KEY_D)) bediening_verwerk_toets(KEY_RIGHT);

        BeginDrawing();
        map_teken();
        entiteit_teken();
        EndDrawing();
    }

    return melding_ok;
}
