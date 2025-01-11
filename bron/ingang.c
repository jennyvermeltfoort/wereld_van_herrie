#include "speler.h"
#include "typen.h"
#include "scherm.h"

int WINAPI WinMain(HINSTANCE instantie ,
                   HINSTANCE instantie_vorige, LPSTR lp_cmd_line,
                   int n_cmd_show) {

    if (scherm_start(instantie, instantie_vorige, lp_cmd_line,
                     n_cmd_show) != melding_ok) {
        return melding_fout;
    }

    return melding_ok;
}
