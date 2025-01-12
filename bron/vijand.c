
#include "entiteit.h"
#include "map.h"
#include "speler.h"



typedef struct {
	richting_t richting;
} vijand_t;

vijand_t vijand = {};
entiteit_t entiteit = {};

vijand_t * vijand_neem(entiteit_t * entiteit) {
	return &vijand; 
}

void vijand_update(entiteit_t *entiteit) {
	vijand_t * vijand = vijand_neem(entiteit);
	entiteit_t * speler = speler_neem();
	entiteit_t * entiteit_preferie = map_entiteit_preferie(entiteit, vijand->richting);
	
	if (speler == entiteit_preferie) {
		entiteit_loop(entiteit, vijand->richting);
		return;
	}

	
}
