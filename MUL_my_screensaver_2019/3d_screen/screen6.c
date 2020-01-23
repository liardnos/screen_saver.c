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

void make_event(f_m_o_t *fmo, int frame, sfEvent event, sfRenderWindow *window)
{
    fmo->angles[0] += 3.14/180/2;
    fmo->angles[1] += 3.14/180/4;
    fmo->angles[2] += 3.14/180/8;
    my_clear_buffer_d(fmo->buf);
    put_in_list_d(fmo);
    if ((frame+1)%500    == 0 && fmo->balls_nb > 3000){
        for (int i = fmo->balls_nb-3000; i < fmo->balls_nb; i++){
            fmo->balls[i%fmo->balls_nb_max][0] = fmo->window_z/2+(
            rand()-1073741824)/21474836;
            fmo->balls[i%fmo->balls_nb_max][1] = fmo->window_z*3/4+(
            rand()-1073741824)/21474836;
            fmo->balls[i%fmo->balls_nb_max][2] = fmo->window_z/2+(
            rand()-1073741824)/21474836;
        }
    }
    fmo->balls_nb < fmo->balls_nb_max ? fmo->balls_nb += 4 : 0;
    while (sfRenderWindow_pollEvent(window, &event))
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
}

void almost_every_things(f_m_o_t *fmo, int i)
{
    fmo->point[0][0] = fmo->balls[i][0];
    fmo->point[0][1] = fmo->balls[i][1];
    fmo->point[0][2] = fmo->balls[i][2];
    fmo->new_point = rotate_points(fmo->point, fmo->center, fmo->angles);
    float d = fmo->new_point[0][2] + fmo->window_z*1.5;
    if (d <= 0) d = 1;
    float ball_size = (fmo->window_z*3.5) / d;
    fmo->cir_pos->x = (fmo->new_point[0][0]-fmo->window_x/2)/
    d*fmo->window_z*2+fmo->window_x/2;
    fmo->cir_pos->y = (fmo->new_point[0][1]-fmo->window_y/2)/
    d*fmo->window_z*2+fmo->window_y/2;
    fmo->window_y/64 < ball_size ? ball_size = fmo->window_y/64 : 0;
    my_draw_circle_d(fmo->buf, *fmo->cir_pos, ball_size, fmo->color);
    free(fmo->new_point[0]);
    free(fmo->new_point);
    sim_type(fmo, i);
}

void almost_every_things2(f_m_o_t *fmo, sfRenderWindow *window,
    sfTexture *texture, sfSprite *sprite)
{
    for (int i = 0; i < fmo->balls_nb; i++){
        fmo->balls[i][0] += fmo->balls[i][3];
        fmo->balls[i][1] += fmo->balls[i][4];
        fmo->balls[i][2] += fmo->balls[i][5];
        int nb = physique_for_i_d(fmo, i);
        fmo->balls[i][3] *= pow(0.997, nb+1);
        fmo->balls[i][4] *= pow(0.997, nb+1);
        fmo->balls[i][5] *= pow(0.997, nb+1);
        /*fmo->color->r = pow(nb, 0.5)*25;
        fmo->color->g = 0;
        fmo->color->b = 255 - pow(nb, 0.5)*25;
        fmo->color->a = 255;*/

        fmo->color->r = 255;// * pow(nb, 0.5) * 0.2;
        fmo->color->g = 240 - pow(nb, 0.7) * 255 * 0.2;
        fmo->color->b = 60;// * pow(nb, 0.5) * 0.2;
        fmo->color->a = 255;
        almost_every_things(fmo, i);
    }
    sfTexture_updateFromPixels(texture, fmo->buf->pixels, fmo->window_x,
    fmo->window_y, 0, 0);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
}

void clean2(f_m_o_t *fmo)
{
    framebuffer_destroy_d(fmo->buf);
    free(fmo->cir_pos);
    free(fmo->color);
    free(fmo->vc1);
    free(fmo->vc2);
    free(fmo->center);
    free(fmo->angles);
    free(fmo->point[0]);
    free(fmo->point);
    for (int i = 0; i < fmo->balls_nb_max; i++)
        free(fmo->balls[i]);
    free(fmo->balls);
    free(fmo);
}

void clean(f_m_o_t *fmo, sfSprite *sprite, sfTexture *texture,
    sfRenderWindow *window)
{
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    for (int i = 0; i < fmo->grille_x; i++){
        for (int ii = 0; ii < fmo->grille_y; ii++){
            for (int iii = 0; iii < fmo->grille_y; iii++)
                linked_list_free_d(fmo->grille[i][ii][iii]);
            free(fmo->grille[i][ii]);
        }
        free(fmo->grille[i]);
    }
    free(fmo->grille);
    clean2(fmo);
}
