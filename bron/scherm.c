
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "bediening.h"
#include "entiteit.h"
#include "map.h"
#include "scherm.h"
#include "speler.h"
#include "stb_image.h"



melding_e scherm_start(void) {
    InitWindow(800, 450, "Wereld van Herrie");
    int width, height, nrChannels;
    unsigned char *data1 =
        stbi_load("middelen/speler_links_stil_1.png", &width, &height, &nrChannels, 4);
    unsigned char *data2 =
        stbi_load("middelen/speler_links_stil_2.png", &width, &height, &nrChannels, 4);
    struct Color *p = (struct Color*) data1; 
    struct Color *c = (struct Color*) data1; 
    struct Color *n = (struct Color*) data2;
    double time = GetTime();

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) bediening_verwerk_toets(KEY_UP);
        if (IsKeyDown(KEY_S)) bediening_verwerk_toets(KEY_DOWN);
        if (IsKeyDown(KEY_A)) bediening_verwerk_toets(KEY_LEFT);
        if (IsKeyDown(KEY_D)) bediening_verwerk_toets(KEY_RIGHT);

        BeginDrawing();

        ClearBackground(WHITE);
        double newTime = GetTime();
        if ((newTime - time) > 0.5) {
            time = newTime;
            struct Color* t = c;
            c = n;
            n = t;
        }
        p = c;

        int schaal = 20;
        int uh = height*schaal;
        int ub = width*schaal;
        for (int y = 0; y < uh; y += schaal) {
            for (int x = 0; x < ub; x += schaal) {
                DrawRectangle(x, y, schaal, schaal, *p++);
            }
        }

        //        map_teken();
        //       entiteit_teken();
        EndDrawing();
    }

    stbi_image_free(data1);
    stbi_image_free(data2);

    return melding_ok;
}
