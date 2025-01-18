
#include "scherm.h"

#include <stdbool.h>

#include "bediening.h"
#include "map.h"
#include "speler.h"

BITMAPINFO kader_bitkaart_info;
HBITMAP kader_bitkaart = 0;
HDC kader_apparaat_context = 0;

scherm_kaderdata_t kaderdata = {};

LRESULT CALLBACK scherm_verwerk_bericht(HWND hendel, UINT bericht,
                                        WPARAM wparam,
                                        LPARAM lparam) {
    switch (bericht) {
        case WM_PAINT: {
            PAINTSTRUCT paint;
            HDC device_context;
            device_context = BeginPaint(hendel, &paint);
            BitBlt(device_context, paint.rcPaint.left,
                   paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left,
                   paint.rcPaint.bottom - paint.rcPaint.top,
                   kader_apparaat_context, paint.rcPaint.left,
                   paint.rcPaint.top, SRCCOPY);
            EndPaint(hendel, &paint);
        } break;

        case WM_SIZE: {
            kader_bitkaart_info.bmiHeader.biWidth = LOWORD(lparam);
            kader_bitkaart_info.bmiHeader.biHeight = HIWORD(lparam);

            if (kader_bitkaart) {
                DeleteObject(kader_bitkaart);
            }

            kader_bitkaart = CreateDIBSection(
                NULL, &kader_bitkaart_info, DIB_RGB_COLORS,
                (void **)&kaderdata.pixels, 0, 0);
            SelectObject(kader_apparaat_context, kader_bitkaart);

            kaderdata.breedte = LOWORD(lparam);
            kaderdata.hoogte = HIWORD(lparam);
        } break;

        case WM_CLOSE: {
            DestroyWindow(hendel);
        } break;

        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;

        case WM_KEYDOWN: {
            bediening_data_t data = {.plat = lparam};
            bediening_verwerk_toets(wparam, &data);
        }; break;

        default: {
            return DefWindowProc(hendel, bericht, wparam, lparam);
        }
    }
    return 0;
}

melding_e scherm_start(HINSTANCE instantie,
                       HINSTANCE instantie_vorige, LPSTR lp_cmd_line,
                       int n_cmd_show) {
    const char naam_klas[] = "HerrieClass";
    WNDCLASS klas = {
        .lpfnWndProc = scherm_verwerk_bericht,
        .hInstance = instantie,
        .lpszClassName = naam_klas,
    };

    if (!RegisterClass(&klas)) {
        return melding_fout;
    }

    kader_bitkaart_info.bmiHeader.biSize =
        sizeof(kader_bitkaart_info.bmiHeader);
    kader_bitkaart_info.bmiHeader.biPlanes = 1;
    kader_bitkaart_info.bmiHeader.biBitCount = 32;
    kader_bitkaart_info.bmiHeader.biCompression = BI_RGB;
    kader_apparaat_context = CreateCompatibleDC(0);

    HWND hendel = CreateWindow(naam_klas, "Wereld van Herrie",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0,
                               950, 950, NULL, NULL, instantie, NULL);

    if (hendel == NULL) {
        return melding_fout;
    }

    map_opslag_e i = map_alloceer();
    map_laad(i, map_id_0);

    ShowWindow(hendel, n_cmd_show);

    MSG bericht = {};
    while (GetMessage(&bericht, NULL, 0, 0) > 0) {
        TranslateMessage(&bericht);
        DispatchMessage(&bericht);

        map_vul_scherm(i, &kaderdata);

        InvalidateRect(hendel, NULL, false);
        UpdateWindow(hendel);
    }

    map_vrijmaken(i);

    return melding_ok;
}
