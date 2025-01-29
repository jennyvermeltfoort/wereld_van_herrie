
#ifndef __WACHTER_SCHADUWPROGRAMMA_H
#define __WACHTER_SCHADUWPROGRAMMA_H

#include <cglm/cglm.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t index;
    uint32_t vao;
} programma_t;

void sp_maak_programma(programma_t *programma, char *bestand_hoek,
                       char *bestand_fragment);
void sp_uniform_zet_bool(programma_t *programma, char *uniform, bool waarde);
void sp_uniform_zet_int(programma_t *programma, char *uniform, uint32_t waarde);
void sp_uniform_zet_float(programma_t *programma, char *uniform, float waarde);
void sp_uniform_zet_m4f(programma_t *programma, char *uniform, mat4 waarde);
void sp_uniform_zet_2f(programma_t *programma, char *uniform, vec2 waarde);
void sp_uniform_zet_2i(programma_t *programma, char *uniform, ivec2 waarde);
void sp_uniform_zet_3f(programma_t *programma, char *uniform, vec3 waarde);
void sp_gebruik(programma_t *programma);
void sp_verwijder(programma_t *programma);

void sp_teken_array(programma_t *programma, ivec2 hoeken);

uint32_t sp_laad_textuur(char *locatie, ivec2 formaat);
void sp_gebruik_textuur(programma_t *programma, uint32_t texture);

#endif  //  __WACHTER_SCHADUWPROGRAMMA_H
