#include "scherm.h"
#include "speler.h"
#include "typen.h"

typedef struct {
    int count;
    int bla;
    int arr[];
} flex_array_t;

int main(void) {

    if (scherm_start() != melding_ok) {
        return melding_fout;
    }

    return melding_ok;
}
