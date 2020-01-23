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

void my_blur_buffer_d(framebuffer_t *buf, float ratio)
{
    int len = buf->width*buf->height*sizeof(sfUint8)*4;

    for (int i = 0; i < len; i++)
        buf->pixels[i] *= ratio;
}

void my_draw_square_d(framebuffer_t *buf, sfVector2u position,
    unsigned int size, sfColor color)
{
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            my_put_pixel_d(buf, position.x+x, position.y+y, color);
}

void my_draw_circle_d(framebuffer_t *buf, sfVector2u position,
    float size, sfColor *color)
{
    for (float x = -1; x <= size*2; x++){
        for (float y = -1; y <= size*2; y++){
            if ((pow((double)x-(float)size, 2) + pow((double)y-(float)size, 2))
            <= pow((double)size, 2)){
                my_put_pixel_d(buf, x + position.x-size, y + position.y-size,
                *color);
            }
        }
    }
}

void linked_list_append_d(struct linked_list_d **begin, int nb)
{
    struct linked_list_d *end = malloc(sizeof(struct linked_list_d));
    end->data = nb;
    end->next = 0;
    struct linked_list_d *mov;
    if (*begin == 0){
        *begin = end;
    } else {
        for (mov = *begin; mov->next; mov = mov->next);
        mov->next = end;
    }
}

int linked_list_free_d(struct linked_list_d *begin)
{
    if (begin == 0)
        return (0);
    struct linked_list_d *last = begin;
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
