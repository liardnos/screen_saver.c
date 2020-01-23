/*
** EPITECH PROJECT, 2019
** bootstrap_coding_style
** File description:
** Main for print
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "framebuffer.h"
#include <stdio.h>
#include <string.h>

void every_things(f_m_o_t *fmo, sfRenderWindow *window, sfTexture *texture,
    sfSprite *sprite)
{
    my_blur_buffer(fmo->buf, 0.9);
    put_in_list(fmo);
    all_i_physique(fmo);
    sfTexture_updateFromPixels(texture, fmo->buf->pixels, fmo->window_x,
    fmo->window_y, 0, 0);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
}

int dd_simu(int mod)
{
    f_m_o_t *fmo = init_fmo();
    sfVideoMode mode = {fmo->window_x, fmo->window_y, 32};
    fmo->mod = mod;
    sfTexture* texture = sfTexture_create(fmo->window_x, fmo->window_y);
    sfSprite* sprite = sfSprite_create();
    sfEvent event;
    sfRenderWindow* window;
    sfSprite_setTexture(sprite, texture, sfTrue);
    window = sfRenderWindow_create(mode, "SFML window", sfClose, 0);
    if (!window || !texture) return EXIT_FAILURE;
    sfRenderWindow_setFramerateLimit(window, 60);
    for (int frame = 0; sfRenderWindow_isOpen(window); frame++) {
        user_interaction(fmo, frame, window);
        while (sfRenderWindow_pollEvent(window, &event))
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        every_things(fmo, window, texture, sprite);
    }
    free_all(fmo, sprite, texture, window);
}
