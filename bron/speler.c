#include "speler.h"

#include "bediening.h"

entiteit_t speler_positie = {};

void speler_verplaats_omhoog(bediening_data_t *data) {
    speler_positie.y += 5 * data->data.herhaal;
}

void speler_verplaats_omlaag(bediening_data_t *data) {
    speler_positie.y -= 5 * data->data.herhaal;
}

void speler_verplaats_links(bediening_data_t *data) {
    speler_positie.x -= 5 * data->data.herhaal;
}

void speler_verplaats_rechts(bediening_data_t *data) {
    speler_positie.x += 5 * data->data.herhaal;
}

entiteit_t *speler_neem_positie(void) { return &speler_positie; }

void speler_prepareer(void) {
    bediening_registreer_toets(bediening_toets_omhoog,
                               speler_verplaats_omhoog);
    bediening_registreer_toets(bediening_toets_omlaag,
                               speler_verplaats_omlaag);
    bediening_registreer_toets(bediening_toets_links,
                               speler_verplaats_links);
    bediening_registreer_toets(bediening_toets_rechts,
                               speler_verplaats_rechts);
    bediening_registreer_toets(bediening_toets_w,
                               speler_verplaats_omhoog);
    bediening_registreer_toets(bediening_toets_s,
                               speler_verplaats_omlaag);
    bediening_registreer_toets(bediening_toets_a,
                               speler_verplaats_links);
    bediening_registreer_toets(bediening_toets_d,
                               speler_verplaats_rechts);
}
