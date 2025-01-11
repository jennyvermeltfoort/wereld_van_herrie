#ifndef __WACHTER_BEDIENING_H
#define __WACHTER_BEDIENING_H

#include <stdint.h>
#include <windows.h>

typedef union {
    struct {
        uint16_t herhaal;
        uint8_t ll;
        uint8_t lh;
    } data;
    uint32_t lparam;
} bediening_data_t;

typedef void (*bediening_toets_cb_t)(bediening_data_t* data);

typedef enum : uint8_t {
    bediening_toets_up = VK_UP,
    bediening_toets_down = VK_DOWN,
    bediening_toets_left = VK_LEFT,
    bediening_toets_right = VK_RIGHT,
    bediening_toets_space = VK_SPACE,
    bediening_toets_w = 0x57,
    bediening_toets_a = 0x41,
    bediening_toets_d = 0x44,
    bediening_toets_s = 0x53,
} bediening_toets_e;

void bediening_registreer_toets(bediening_toets_e toets, bediening_toets_cb_t cb);
void bediening_verwerk_toets(bediening_toets_e toets, bediening_data_t* data);

#endif  // __WACHTER_BEDIENING_H
