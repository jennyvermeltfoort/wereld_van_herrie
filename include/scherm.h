

#ifndef __WACHTER_SCHERM_H
#define __WACHTER_SCHERM_H

#include <windows.h>

#include "types.h"

errno_e scherm_start(HINSTANCE instantie,
                     HINSTANCE instantie_vorige, LPSTR lp_cmd_line,
                     int n_cmd_show);

#endif  // __WACHTER_SCHERM_H
