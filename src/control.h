#ifndef __GUARD_CONTROL_H
#define __GUARD_CONTROL_H

#include <stdint.h>
#include <windows.h>

typedef union {
    struct {
        uint16_t repeat;
        uint8_t ll;
        uint8_t lh;
    } data;
    uint32_t lparam;
} control_kdata_t;

typedef void (*control_key_cb_t)(control_kdata_t* kdata);

typedef enum : uint8_t {
    control_key_up = VK_UP,
    control_key_down = VK_DOWN,
    control_key_left = VK_LEFT,
    control_key_right = VK_RIGHT,
    control_key_space = VK_SPACE,
    control_key_w = 0x57,
    control_key_a = 0x41,
    control_key_d = 0x44,
    control_key_s = 0x53,
} control_key_e;

void control_reg_key(control_key_e key, control_key_cb_t cb);
void control_proc_key(control_key_e key, control_kdata_t* kdata);

#endif  // __GUARD_CONTROL_H
