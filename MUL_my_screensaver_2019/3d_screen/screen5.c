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

int interact_with_ii_d(f_m_o_t *fmo, int i, int ii)
{
    if (i <= ii) return (0);
    float dx = fmo->balls[ii][0] - fmo->balls[i][0];
    float dy = fmo->balls[ii][1] - fmo->balls[i][1];
    float dz = fmo->balls[ii][2] - fmo->balls[i][2];
    float pdx = pow(dx, 2);
    float pdy = pow(dy, 2);
    float pdz = pow(dz, 2);
    float dxyz = pdx + pdy + pdz;
    if (dxyz > fmo->interact_range_sqr) return (0);
    float f = 1/(dxyz+200)*300;
    float dxy = pow(pdx + pdy, 0.5);
    float dxz = pow(pdx + pdz, 0.5);
    float anglexy = acos(dx/dxy);
    float anglexz = acos(dx/dxz);
    dy < 0 ? anglexy *= -1 : 0, dz < 0 ? anglexz *= -1 : 0;
    fmo->balls[i][3] -= f*cos(anglexy), fmo->balls[i][4] -= f*sin(anglexy);
    fmo->balls[i][5] -= f*sin(anglexz), fmo->balls[ii][3] += f*cos(anglexy);
    fmo->balls[ii][4] += f*sin(anglexy);
    fmo->balls[ii][5] += f*sin(anglexz);
    return (1);
}

int physique_for_i2(f_m_o_t *fmo, int x, int y, int z)
{
    int nb = 0;
    for (int xx = 0; xx < 27; xx++){
        if (x+xx%3-1 < fmo->grille_x && x+xx%3-1 >= 0 && y+(xx%9)/3-1 <
        fmo->grille_y && y+(xx%9)/3-1 >= 0 && z+xx/9-1 < fmo->grille_z &&
        z+xx/9-1 >= 0){
            struct linked_list_d *mov =
            fmo->grille[x+xx%3-1][y+(xx%9)/3-1][z+xx/9-1];
            for (; mov; mov = mov->next){
                int ii = mov->data;
                nb += interact_with_ii_d(fmo, fmo->i, ii);
            }
        }
    }
    return (nb);
}

int physique_for_i_d(f_m_o_t *fmo, int i)
{
    fmo->i = i;
    int x = fmo->balls[i][0]/fmo->interact_range;
    int y = fmo->balls[i][1]/fmo->interact_range;
    int z = fmo->balls[i][2]/fmo->interact_range;
    x < 0 ? x = 0 : 0;
    x > fmo->grille_x ? x = fmo->grille_x : 0;
    y < 0 ? y = 0 : 0;
    y > fmo->grille_y ? y = fmo->grille_y : 0;
    z < 0 ? z = 0 : 0;
    z > fmo->grille_z ? z = fmo->grille_z : 0;
    return (physique_for_i2(fmo, x, y, z));
}

void sim_type(f_m_o_t *fmo, int i)
{
    if (fmo->mod == 1){
        fmo->balls[i][3] += (fmo->window_x/2-fmo->balls[i][0])/10000;
        fmo->balls[i][5] += (fmo->window_y/2-fmo->balls[i][2])/10000;
        fmo->balls[i][4] += (fmo->window_z/2-fmo->balls[i][1])/10000;
    } else {
        fmo->balls[i][4] += 0.1;
        if (fmo->balls[i][1] > fmo->window_z*0.9)
            fmo->balls[i][4] -= (fmo->balls[i][1]-fmo->window_z*0.9)/10;
        if (fmo->balls[i][0] < fmo->window_z*0.1)
            fmo->balls[i][3] -= (fmo->balls[i][0]-fmo->window_z*0.1)/10;
        if (fmo->balls[i][0] > fmo->window_z*0.9)
            fmo->balls[i][3] -= (fmo->balls[i][0]-fmo->window_z*0.9)/10;
        if (fmo->balls[i][2] < fmo->window_z*0.1)
            fmo->balls[i][5] -= (fmo->balls[i][2]-fmo->window_z*0.1)/10;
        if (fmo->balls[i][2] > fmo->window_z*0.9)
            fmo->balls[i][5] -= (fmo->balls[i][2]-fmo->window_z*0.9)/10;
    }
}
