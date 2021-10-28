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

int linked_list_len_d(struct linked_list_d *begin)
{
    if (begin == 0)
        return (0);
    int len = 1;
    for (; begin->next; begin = begin->next);
    return (len);
}

void init_fmo2_d(f_m_o_t *fmo)
{
    fmo->balls = malloc((fmo->balls_nb+1)*sizeof(int *));
    fmo->balls[fmo->balls_nb] = 0;
    for (int i = 0; i < fmo->balls_nb; i++){
        fmo->balls[i] = malloc(6*sizeof(float));
        fmo->balls[i][0] = fmo->window_z/2+(rand()-1073741824)/21474836;
        fmo->balls[i][1] = fmo->window_z/4+(rand()-1073741824)/21474836;
        fmo->balls[i][2] = fmo->window_z/2+(rand()-1073741824)/21474836;
        fmo->balls[i][3] = 0;
        fmo->balls[i][4] = 0;
        fmo->balls[i][5] = 0;
    }
    fmo->buf = framebuffer_create_d(fmo->window_x, fmo->window_y);
    fmo->cir_pos = malloc(sizeof(sfVector2u));
    fmo->color = malloc(sizeof(sfColor));
    fmo->balls_nb = 0;
    fmo->vc1 = malloc(sizeof(sfVector2u));
    fmo->vc2 = malloc(sizeof(sfVector2u));
}

void init_fmo3(f_m_o_t *fmo)
{
    fmo->center = malloc(sizeof(float)*3);
    fmo->center[0] = fmo->window_x/2;
    fmo->center[1] = fmo->window_y/2;
    fmo->center[2] = fmo->window_z/2;
    fmo->angles = malloc(sizeof(float)*3);
    fmo->angles[0] = 0;
    fmo->angles[1] = 0;
    fmo->angles[2] = 0;
    fmo->point = malloc(sizeof(float *)*2);
    memset(fmo->point, 0, sizeof(float *)*2);
    fmo->point[0] = malloc(sizeof(float)*3);
    memset(fmo->point[0], 0, sizeof(float)*3);
}

f_m_o_t *init_fmo_d(void)
{
    f_m_o_t *fmo = malloc(sizeof(f_m_o_t));
    fmo->window_x = 900, fmo->window_y = 900, fmo->window_z = 900;
    fmo->balls_nb = 15000, fmo->balls_nb_max = fmo->balls_nb;
    fmo->interact_range = 30;
    fmo->interact_range_sqr = pow(fmo->interact_range, 2);
    fmo->grille_x = fmo->window_x/fmo->interact_range + 1;
    fmo->grille_y = fmo->window_y/fmo->interact_range + 1;
    fmo->grille_z = fmo->window_z/fmo->interact_range + 1;
    fmo->grille = malloc((fmo->grille_x+1) * sizeof(void *));
    memset(fmo->grille, 0, (fmo->grille_x + 1) * sizeof(void *  ));
    for (int i = 0; i < fmo->grille_x; i++){
        fmo->grille[i] = malloc(sizeof(void *)*(fmo->grille_y + 1));
        memset(fmo->grille[i], 0, sizeof(void *)*(fmo->grille_y + 1));
        for (int ii = 0; ii < fmo->grille_y; ii++){
            fmo->grille[i][ii] = malloc(sizeof(void *)*(fmo->grille_z + 1));
            memset(fmo->grille[i][ii], 0, sizeof(void *)*(fmo->grille_z + 1));
        }
    }
    init_fmo2_d(fmo), init_fmo3(fmo);
    return (fmo);
}

void put_in_list_d(f_m_o_t *fmo)
{
    for (int i = 0; i < fmo->grille_x; i++)
        for (int ii = 0; ii < fmo->grille_y; ii++)
            for (int iii = 0; iii < fmo->grille_z; iii++)
                linked_list_free_d(fmo->grille[i][ii][iii]);
    for (int i = 0; i < fmo->grille_x; i++)
        for (int ii = 0; ii < fmo->grille_y; ii++)
            memset(fmo->grille[i][ii], 0, sizeof(void *)*(fmo->grille_z + 1));
    for (int i = 0; i < fmo->balls_nb; i++){
        int x = fmo->balls[i][0]/fmo->interact_range;
        int y = fmo->balls[i][1]/fmo->interact_range;
        int z = fmo->balls[i][2]/fmo->interact_range;
        x < 0 ? x = 0 : 0;
        x > fmo->grille_x-1 ? x = fmo->grille_x-1 : 0;
        y < 0 ? y = 0 : 0;
        y > fmo->grille_y-1 ? y = fmo->grille_y-1 : 0;
        z < 0 ? z = 0 : 0;
        z > fmo->grille_z-1 ? z = fmo->grille_z-1 : 0;
        linked_list_append_d(&fmo->grille[x][y][z], i);
    }
}
