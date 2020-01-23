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

void init_fmo2(f_m_o_t *fmo)
{
    fmo->balls = malloc((fmo->balls_nb+1)*sizeof(int *));
    fmo->balls[fmo->balls_nb] = 0;
    fmo->sqrt = pow(fmo->balls_nb, 0.5);
    for (int i = 0; i < fmo->balls_nb; i++){
        fmo->balls[i] = malloc(5*sizeof(float));
        fmo->balls[i][0] = fmo->window_x/9 + rand()/21474836/2;
        fmo->balls[i][1] = fmo->window_y/10 + rand()/21474836/2;
        fmo->balls[i][2] = 0;
        fmo->balls[i][3] = 0;
        fmo->balls[i][4] = 0;
    }
    fmo->buf = framebuffer_create(fmo->window_x, fmo->window_y);
    fmo->cir_pos = malloc(sizeof(sfVector2u));
    fmo->color = malloc(sizeof(sfColor));
    fmo->balls_nb = 0;
    fmo->vc1 = malloc(sizeof(sfVector2u));
    fmo->vc2 = malloc(sizeof(sfVector2u));
}

f_m_o_t *init_fmo(void)
{
    f_m_o_t *fmo = malloc(sizeof(f_m_o_t));
    fmo->window_x = 1200;
    fmo->window_y = 800;
    fmo->balls_nb = 4000;
    fmo->balls_nb_max = fmo->balls_nb;
    fmo->interact_range = 40;
    fmo->interact_range_sqr = pow(fmo->interact_range, 2);
    fmo->grille_x = fmo->window_x/fmo->interact_range + 1;
    fmo->grille_y = fmo->window_y/fmo->interact_range + 1;
    fmo->gri = malloc((fmo->grille_x+1) * sizeof(void *));
    memset(fmo->gri, 0, (fmo->grille_x + 1) * sizeof(void *  ));
    for (int i = 0; i < fmo->grille_x; i++){
        fmo->gri[i] = malloc(sizeof(void *)*(fmo->grille_y + 1));
        memset(fmo->gri[i], 0, sizeof(void *)*(fmo->grille_y + 1));
    }
    init_fmo2(fmo);
    return (fmo);
}

void user_interaction2(f_m_o_t *fmo, int frame)
{
    fmo->balls_nb < fmo->balls_nb_max ? fmo->balls_nb += 1 : 0;
    if (fmo->mouse_vec.x > 0 && fmo->mouse_vec.x < fmo->window_x &&
    fmo->mouse_vec.y > 0 && fmo->mouse_vec.y < fmo->window_y){
        fmo->balls[frame%fmo->balls_nb_max][0] = fmo->mouse_vec.x+rand_2()/2;
        fmo->balls[frame%fmo->balls_nb_max][1] = fmo->mouse_vec.y+rand_2()/2;
    }
}

void user_interaction(f_m_o_t *fmo, int frame, sfRenderWindow *window)
{
    fmo->mouse_vec.x = -1;
    fmo->mouse_vec.y = -1;
    if ((frame+1)%500 == 0 && frame > 1000){
        for (int i = frame-500; i < frame; i++){
            if (fmo->mouse_vec.x > 0 && fmo->mouse_vec.x < fmo->window_x &&
            fmo->mouse_vec.y > 0 && fmo->mouse_vec.y < fmo->window_y){
                fmo->balls[i%fmo->balls_nb_max][0] = fmo->mouse_vec.x+rand_2();
                fmo->balls[i%fmo->balls_nb_max][1] = fmo->mouse_vec.y+rand_2();
            } else {
                fmo->balls[i%fmo->balls_nb_max][0] = fmo->window_x/2+rand_2();
                fmo->balls[i%fmo->balls_nb_max][1] = fmo->window_y*3/4+rand_2();
            }
        }
    }
    user_interaction2(fmo, frame);
}

void free_all(f_m_o_t *fmo, sfSprite *sprite, sfTexture *texture,
    sfRenderWindow *window)
{
    for (int i = 0; i < fmo->grille_x; i++){
        for (int ii = 0; ii < fmo->grille_y; ii++)
            linked_list_free(fmo->gri[i][ii]);
        free(fmo->gri[i]);
    }
    free(fmo->gri);
    framebuffer_destroy(fmo->buf);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    free(fmo->cir_pos);
    free(fmo->color);
    free(fmo->vc1);
    free(fmo->vc2);
    for (int i = 0; i < fmo->balls_nb_max; i++)
        free(fmo->balls[i]);
    free(fmo->balls);
    free(fmo);
}
