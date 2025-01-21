#include "bediening.h"
#include "speler.h"

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
    bediening_registreer_toets(KEY_UP,
                               speler_verplaats_omhoog);
    bediening_registreer_toets(KEY_DOWN,
                               speler_verplaats_omlaag);
    bediening_registreer_toets(KEY_LEFT,
                               speler_verplaats_links);
    bediening_registreer_toets(KEY_RIGHT,
                               speler_verplaats_rechts);
    bediening_registreer_toets(KEY_W,
                               speler_verplaats_omhoog);
    bediening_registreer_toets(KEY_S,
                               speler_verplaats_omlaag);
    bediening_registreer_toets(KEY_A,
                               speler_verplaats_links);
    bediening_registreer_toets(KEY_D,
                               speler_verplaats_rechts);
}
