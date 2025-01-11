
#ifndef __GUARD_PLAYER_H
#define __GUARD_PLAYER_H

#include <stdint.h>

#include "types.h"
#include "entity.h"

entity_position_t* player_get_position(void);
void player_init(void);

#endif  // __GUARD_PLAYER_H
