
#ifndef __WACHTER_SCHADUWPROGRAMMA_H
#define __WACHTER_SCHADUWPROGRAMMA_H

#include <stdint.h>
#include <stdio.h>

uint32_t sp_maak_programma(char *bestand_hoek,
                           char *bestand_fragment);
void sp_uniform_zet_bool(uint32_t programma, char *uniform,
                         bool waarde);
void sp_uniform_zet_int(uint32_t programma, char *uniform,
                        uint32_t waarde);
void sp_uniform_zet_float(uint32_t programma, char *uniform,
                          float waarde);
void sp_gebruik(uint32_t programma);
void sp_verwijder(uint32_t programma);

#endif  //  __WACHTER_SCHADUWPROGRAMMA_H
