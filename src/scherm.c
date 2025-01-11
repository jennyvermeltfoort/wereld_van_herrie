#include "scherm.h"

#include <stdint.h>
#include <stdio.h>

#include "bediening.h"
#include "speler.h"

BITMAPINFO frame_bitmap_info;
HBITMAP frame_bitmap = 0;
HDC frame_device_context = 0;

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t *pixels;
} window_framedata_t;

window_framedata_t framedata = {};

LRESULT CALLBACK window_proc(HWND handle, UINT message, WPARAM wparam,
                             LPARAM lparam) {
    switch (message) {
        case WM_PAINT: {
            PAINTSTRUCT paint;
            HDC device_context;
            device_context = BeginPaint(handle, &paint);
            BitBlt(device_context, paint.rcPaint.left,
                   paint.rcPaint.top,
                   paint.rcPaint.right - paint.rcPaint.left,
                   paint.rcPaint.bottom - paint.rcPaint.top,
                   frame_device_context, paint.rcPaint.left,
                   paint.rcPaint.top, SRCCOPY);
            EndPaint(handle, &paint);
        } break;

        case WM_SIZE: {
            frame_bitmap_info.bmiHeader.biWidth = LOWORD(lparam);
            frame_bitmap_info.bmiHeader.biHeight = HIWORD(lparam);

            if (frame_bitmap) {
                DeleteObject(frame_bitmap);
            }

            frame_bitmap = CreateDIBSection(
                NULL, &frame_bitmap_info, DIB_RGB_COLORS,
                (void **)&framedata.pixels, 0, 0);
            SelectObject(frame_device_context, frame_bitmap);

            framedata.width = LOWORD(lparam);
            framedata.height = HIWORD(lparam);
        } break;

        case WM_CLOSE: {
            DestroyWindow(handle);
        } break;

        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;

        case WM_KEYDOWN: {
            control_kdata_t kdata = {.lparam = lparam};
            control_proc_key(wparam, &kdata);
        }; break;

        default: {
            return DefWindowProc(handle, message, wparam, lparam);
        }
    }
    return 0;
}

errno_e window_start(HINSTANCE h_instance,
                     HINSTANCE h_previous_instance, LPSTR lp_cmd_line,
                     int n_cmd_show) {
    const char class_name[] = "HerrieClass";
    WNDCLASS class = {
        .lpfnWndProc = window_proc,
        .hInstance = h_instance,
        .lpszClassName = class_name,
    };

    if (!RegisterClass(&class)) {
        return errno_err;
    }

    frame_bitmap_info.bmiHeader.biSize =
        sizeof(frame_bitmap_info.bmiHeader);
    frame_bitmap_info.bmiHeader.biPlanes = 1;
    frame_bitmap_info.bmiHeader.biBitCount = 32;
    frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
    frame_device_context = CreateCompatibleDC(0);

    HWND handle =
        CreateWindow(class_name, "Wereld van Herrie",
                     WS_OVERLAPPEDWINDOW | WS_VISIBLE, 640, 300, 640,
                     480, NULL, NULL, h_instance, NULL);

    if (handle == NULL) {
        return errno_err;
    }

    entity_position_t *player_position = player_get_position();
    ShowWindow(handle, n_cmd_show);

    MSG message = {};
    while (GetMessage(&message, NULL, 0, 0) > 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);

        for (uint32_t y = 0; y < framedata.height; y++) {
            for (uint32_t x = 0; x < framedata.width; x++) {
                framedata.pixels[y * framedata.width + x] = 0;
            }
        }

        for (uint32_t i = 0; i < 10; i++) {
            for (uint32_t y = 0; y < 5; y++) {
                framedata.pixels[(i + player_position->y) *
                                     framedata.width +
                                 player_position->x + y] = 0xFFFFFF;
            }
        }

        InvalidateRect(handle, NULL, false);
        UpdateWindow(handle);
    }

    return errno_ok;
}
