#include "speler.h"
#include "typen.h"
#include "scherm.h"

int WINAPI WinMain(HINSTANCE h_instance,
                   HINSTANCE h_previous_instance, LPSTR lp_cmd_line,
                   int n_cmd_show) {
    player_init();

    if (window_start(h_instance, h_previous_instance, lp_cmd_line,
                     n_cmd_show) != errno_ok) {
        return errno_err;
    }

    return errno_ok;
}
