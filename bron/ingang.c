#include "scherm.h"
#include "speler.h"
#include "typen.h"

typedef struct {
    int count;
    int bla;
    int arr[];
} flex_array_t;

int WINAPI WinMain(HINSTANCE instantie, HINSTANCE instantie_vorige,
                   LPSTR lp_cmd_line, int n_cmd_show) {
    if (scherm_start(instantie, instantie_vorige, lp_cmd_line,
                     n_cmd_show) != melding_ok) {
        return melding_fout;
    }

    return melding_ok;
}
