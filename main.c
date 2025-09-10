#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "graphics.h"

#define WIDTH 100
#define HEIGHT 100
#define SCALE 8


void main()
{
    gfx_init(WIDTH, HEIGHT, SCALE);

    gfx_clear_pixels();
    gfx_update_window();

    gfx_set_pixel(255,   0,     0, 0, 0);
    gfx_set_pixel(0,   255,     0, 1, 0);
    gfx_set_pixel(0,     0,   255, 0, 1);

    for (int y = 0; y < HEIGHT; y += 1)
    {
        for (int x = 0; x < WIDTH; x += 1)
        {
            int r = x % 2 ? 0 : 255;
            int g = y % 2 ? 0 : 255;
            int b = (x + y) % 256;

            gfx_set_pixel(r, g, b, x, y);
        }
    }

    gfx_update_window();
    gfx_wait_for_quit();
}
