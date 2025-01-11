

#include "control.h"

void control_key_stub(control_kdata_t *kdata) {}

control_key_cb_t key_cbs[0XFF] = {control_key_stub};

void control_reg_key(control_key_e key, control_key_cb_t cb) {
    key_cbs[key] = cb;
}

void control_proc_key(control_key_e key, control_kdata_t *kdata) {
    key_cbs[key](kdata);
}
