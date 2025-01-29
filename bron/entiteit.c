
#include "entiteit.h"

#define MIDDEL_Z 0.35f  // 0.35 want het model van de sprite is geroteerd met 45 graden.
#define MIDDEL_X 0.35f  // dus 0 -> 0.7 en 0.7/2 = 0.35

// Entiteit is gepositioneert op x - 0.5, z - 0.5 vanwegen de locatie binnen de wereld.
// x, z zijn de links bovens coordinaten van een block. dus - MIDDEL_Z en MIDDEL_X is de
// center van het blok.

unsigned char wereld_entiteiten_id[WORLD_Z][WORLD_X] = {0};
entiteit_t wereld_entiteiten[WORLD_Z][WORLD_X] = {0};
uint32_t id_index = 1;

uint32_t wereld_entiteit_maak_id(void) { return id_index++; }

void wereld_entiteit_voegtoe(vec3 positie, unsigned char id, unsigned int texture,
                             ivec2 hoeken) {
    entiteit_t *e =
        &wereld_entiteiten[(int)(positie[2] + MIDDEL_Z)][(int)(positie[0] + MIDDEL_X)];
    e->hoeken[0] = hoeken[0];
    e->hoeken[1] = hoeken[1];
    e->texture = texture;
    e->positie[0] = positie[0];
    e->positie[1] = positie[1];
    e->positie[2] = positie[2];
    wereld_entiteiten_id[(int)(positie[2] + MIDDEL_Z)][(int)(positie[0] + MIDDEL_X)] = id;
}

void wereld_entiteit_verwijder(vec3 positie) {
    wereld_entiteiten_id[(int)(positie[2] + MIDDEL_Z)][(int)(positie[0] + MIDDEL_X)] = 0;
}

uint32_t wereld_entiteit_id(vec3 positie) {
    return wereld_entiteiten_id[(int)(positie[2] + MIDDEL_Z)]
                               [(int)(positie[0] + MIDDEL_X)];
}

entiteit_t *wereld_entiteit_neem(vec3 positie) {
    return &wereld_entiteiten[(int)(positie[2] + MIDDEL_Z)][(int)(positie[0] + MIDDEL_X)];
}
