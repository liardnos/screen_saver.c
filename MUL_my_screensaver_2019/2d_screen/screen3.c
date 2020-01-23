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

void my_draw_lines(framebuffer_t *buf, sfVector2u **vects, int n, sfColor color)
{
    for (int i = 0; i < n-1; i++){
        my_draw_line(buf, vects[i], vects[i+1], color);
    }
}

void linked_list_append(struct linked_list **begin, int nb)
{
    struct linked_list *end = malloc(sizeof(struct linked_list));
    end->data = nb;
    end->next = 0;
    struct linked_list *mov;
    if (*begin == 0){
        *begin = end;
    } else {
        for (mov = *begin; mov->next; mov = mov->next);
        mov->next = end;
    }
}

int linked_list_free(struct linked_list *begin)
{
    if (begin == 0)
        return (0);
    struct linked_list *last = begin;
    if (begin->next != 0){
        for (begin = begin->next; begin->next; begin = begin->next){
            free(last);
            last = begin;
        }
        free(last);
    }
    free(begin);
    return (1);
}

int linked_list_len(struct linked_list *begin)
{
    if (begin == 0)
        return (0);
    int len = 1;
    for (; begin->next; begin = begin->next);
    return (len);
}

int interact_with_ii(int i, int p, f_m_o_t *fmo)
{
    if (i != p){
        float dx = fmo->balls[p][0] - fmo->balls[i][0];
        float dy = fmo->balls[p][1] - fmo->balls[i][1];
        float dxy = pow(dx, 2) + pow(dy, 2);
        if (dxy < fmo->interact_range_sqr){
            dxy = pow(dxy, 0.5);
            float angle = acos(dx/dxy);
            dy < 0 ? angle *= -1 : 0;
            float f = 1/pow(dxy+5, 2)*200;
            fmo->balls[i][2] -= f*cos(angle), fmo->balls[i][3] -= f*sin(angle);
            fmo->vc1->y = fmo->balls[i][1], fmo->vc1->x = fmo->balls[i][0];
            fmo->vc2->x = fmo->balls[p][0], fmo->vc2->y = fmo->balls[p][1];
            fmo->color->r = (1-dxy/fmo->interact_range)*255;
            fmo->color->g = 0, fmo->color->b = 0, fmo->color->a = 255;
            if (fmo->mod)
                my_draw_line(fmo->buf, fmo->vc1, fmo->vc2, *fmo->color);
            return (1);
        }
    }
    return (0);
}
