/*
** EPITECH PROJECT, 2019
** bootstrap_3D_coding_style
** File description:
** Main for print
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <math.h>
#include "framebuffer.h"
#include <stdio.h>
#include <string.h>

int ddd_simu(int mod)
{
    f_m_o_t *fmo = init_fmo_d();
    fmo->mod = mod;
    sfVideoMode mode = {fmo->window_x, fmo->window_y, 32};
    sfRenderWindow *window;
    sfTexture *texture;
    sfSprite *sprite;
    sfEvent event;
    framebuffer_t *framebuffer;
    window = sfRenderWindow_create(mode, "SFML window", sfClose, 0);
    if (!window) return EXIT_FAILURE;
    texture = sfTexture_create(fmo->window_x, fmo->window_y);
    if (!texture) return EXIT_FAILURE;
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfRenderWindow_setFramerateLimit(window, 60);
    for (int frame = 0; sfRenderWindow_isOpen(window); frame++){
        make_event(fmo, frame, event, window);
        almost_every_things2(fmo, window, texture, sprite);
    }
    clean(fmo, sprite, texture, window);
}
