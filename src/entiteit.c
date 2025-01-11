#include "entiteit.h"


entity_list_t lists[entity_draw_prio_null] = {};


void entity_prio_list_init(entity_prio_list_t *list, entity_draw_prio_t prio) {
	lists[prio] = list;
}

entity_list_t * entity_get_by_priority(entity_draw_prio_t prio) {
	return lists[prio];
}
