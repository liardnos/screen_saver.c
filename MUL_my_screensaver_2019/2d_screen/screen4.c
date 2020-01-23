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

float rand_2(void)
{
    return (rand()-1073741824)/21474836;
}

int physique_for_i(f_m_o_t *fmo, int i)
{
    int nb = 0;
    int x = fmo->balls[i][0]/fmo->interact_range;
    int y = fmo->balls[i][1]/fmo->interact_range;
    x < 0 ? x = 0 : 0;
    x > fmo->grille_x ? x = fmo->grille_x : 0;
    y < 0 ? y = 0 : 0;
    y > fmo->grille_y ? y = fmo->grille_y : 0;
    for (int xx = 0; xx < 9; xx++){
        if (x+xx%3-1 < fmo->grille_x && x+xx%3-1 >= 0 && y+xx/3-1 <
        fmo->grille_y && y+xx/3-1 >= 0){
            struct linked_list *mov = fmo->gri[x+xx%3-1][y+xx/3-1];
            for (; mov; mov = mov->next){
                int ii = mov->data;
                nb += interact_with_ii(i, ii, fmo);
            }
        }
    }
    return (nb);
}

void put_in_list(f_m_o_t *fmo)
{
    for (int i = 0; i < fmo->grille_x; i++)
        for (int ii = 0; ii < fmo->grille_y; ii++)
            linked_list_free(fmo->gri[i][ii]);
    for (int i = 0; i < fmo->grille_x; i++)
        memset(fmo->gri[i], 0, sizeof(void *)*(fmo->grille_y + 1));
    for (int i = 0; i < fmo->balls_nb; i++){
        int x = fmo->balls[i][0]/fmo->interact_range;
        int y = fmo->balls[i][1]/fmo->interact_range;
        x < 0 ? x = 0 : 0;
        x > fmo->grille_x-1 ? x = fmo->grille_x-1 : 0;
        y < 0 ? y = 0 : 0;
        y > fmo->grille_y-1 ? y = fmo->grille_y-1 : 0;
        linked_list_append(&fmo->gri[x][y], i);
    }
}

void wall_physique(f_m_o_t *fmo, int i)
{
    if (fmo->balls[i][1] > fmo->window_y*0.9)
        fmo->balls[i][3] -= (fmo->balls[i][1]-fmo->window_y*0.9)/10;
    if (fmo->balls[i][0] < fmo->window_x*0.1)
        fmo->balls[i][2] -= (fmo->balls[i][0]-fmo->window_x*0.1)/10;
    if (fmo->balls[i][0] > fmo->window_x*0.9)
        fmo->balls[i][2] -= (fmo->balls[i][0]-fmo->window_x*0.9)/10;
}

void all_i_physique(f_m_o_t *fmo)
{
    for (int i = 0; i < fmo->balls_nb; i++){
        fmo->balls[i][0] += fmo->balls[i][2];
        fmo->balls[i][1] += fmo->balls[i][3];
        fmo->balls[i][2] += fmo->balls[i][4];
        fmo->balls[i][3] += 0.2;
        int nb = physique_for_i(fmo, i);
        fmo->balls[i][2] *= pow(0.996, nb);
        fmo->balls[i][3] *= pow(0.996, nb);
        fmo->color->r = pow(nb, 0.5)*25;
        fmo->color->g = 0;
        fmo->color->b = 255-pow(nb, 0.5)*25, fmo->color->a = 255;
        fmo->cir_pos->x = fmo->balls[i][0];
        fmo->cir_pos->y = fmo->balls[i][1];
        if (fmo->mod == 0)
            my_draw_circle(fmo->buf, *fmo->cir_pos, 3, fmo->color);
        wall_physique(fmo, i);
    }
}
