

#ifndef __GUARD_WINDOW_H
#define __GUARD_WINDOW_H

#include <windows.h>

#include "types.h"

errno_e window_start(HINSTANCE h_instance,
                     HINSTANCE h_previous_instance, LPSTR lp_cmd_line,
                     int n_cmd_show);

#endif  // __GUARD_WINDOW_H
