#include <assert.h>
#include <pthread.h>
#include <SDL.h>

#include "graphics.h"

struct gfx
{
    int scale;
};

static SDL_Window *window;
static SDL_Surface *surface;
static SDL_Rect screen = {.x = 0, .y = 0};
static struct gfx gfx = {.scale = 1};



void gfx_wait_for_quit()
{
    SDL_Event event;
    for (;;) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
          printf("QUIT event\n");
          break;
        }
    }

    printf("bye\n");
}


void gfx_init(int width, int height, int scale)
{
    screen.w = width * scale;
    screen.h = height * scale;
    gfx.scale = scale;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("cray",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              screen.w, screen.h,
                              SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);

    /* we only support a specific pixel format below */
    SDL_PixelFormat* format = surface->format;
    assert(format->format == SDL_PIXELFORMAT_RGB888);
    assert(format->Rmask == 0xff0000);
    assert(format->Gmask == 0x00ff00);
    assert(format->Bmask == 0x0000ff);
    assert(format->Amask == 0x0);
    assert(format->BitsPerPixel == 32);
    assert(format->BytesPerPixel == 4);
}


void gfx_set_pixel(int r, int g, int b, int x, int y)
{
    Uint32 pixel = (r << 16) | (g << 8) | b;

    int start_x = x * gfx.scale;
    int start_y = y * gfx.scale;

    int end_x = (x + 1) * gfx.scale;
    int end_y = (y + 1) * gfx.scale;


    for (int ly = start_y; ly < end_y; ly += 1)
    {
        for (int lx = start_x; lx < end_x; lx += 1)
        {

            size_t i = (ly * surface->pitch) / sizeof(Uint32) + lx;
            ((Uint32*)surface->pixels)[i] = pixel;
        }
    }
}

void gfx_clear_pixels()
{
    int res = SDL_FillRect(surface, &screen, 0xffffffff);
    assert(res == 0);
}


void gfx_update_window()
{
    int res = SDL_UpdateWindowSurface(window);
    assert(res == 0);
}
