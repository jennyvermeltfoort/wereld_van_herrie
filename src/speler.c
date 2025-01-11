#include "speler.h"

#include "bediening.h"

entity_position_t player_position = {};

void player_move_up(control_kdata_t *kdata) {
    player_position.y += 5 * kdata->data.repeat;
}

void player_move_down(control_kdata_t *kdata) {
    player_position.y -= 5 * kdata->data.repeat;
}

void player_move_left(control_kdata_t *kdata) {
    player_position.x -= 5 * kdata->data.repeat;
}

void player_move_right(control_kdata_t *kdata) {
    player_position.x += 5 * kdata->data.repeat;
}

entity_position_t *player_get_position(void) {
    return &player_position;
}

void player_init(void) {
    control_reg_key(control_key_up, player_move_up);
    control_reg_key(control_key_down, player_move_down);
    control_reg_key(control_key_left, player_move_left);
    control_reg_key(control_key_right, player_move_right);
    control_reg_key(control_key_w, player_move_up);
    control_reg_key(control_key_s, player_move_down);
    control_reg_key(control_key_a, player_move_left);
    control_reg_key(control_key_d, player_move_right);
}
