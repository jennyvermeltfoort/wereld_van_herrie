
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

void wereld_entiteit_voegtoe(vec3s positie, unsigned char id, unsigned int texture,
                             unsigned char start, unsigned char eind) {
    entiteit_t *e =
        &wereld_entiteiten[(int)(positie.z + MIDDEL_Z)][(int)(positie.x + MIDDEL_X)];
    e->start = start;
    e->eind = eind;
    e->texture = texture;
    e->positie = positie;
    wereld_entiteiten_id[(int)(positie.z + MIDDEL_Z)][(int)(positie.x + MIDDEL_X)] = id;
}

void wereld_entiteit_verwijder(vec3s positie) {
    wereld_entiteiten_id[(int)(positie.z + MIDDEL_Z)][(int)(positie.x + MIDDEL_X)] = 0;
}

uint32_t wereld_entiteit_id(vec3s positie) {
    return wereld_entiteiten_id[(int)(positie.z + MIDDEL_Z)][(int)(positie.x + MIDDEL_X)];
}

entiteit_t *wereld_entiteit_neem(vec3s positie) {
    return &wereld_entiteiten[(int)(positie.z + MIDDEL_Z)][(int)(positie.x + MIDDEL_X)];
}
