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

void my_blur_buffer(framebuffer_t *buf, float ratio)
{
    int len = buf->width*buf->height*sizeof(sfUint8)*4;

    for (int i = 0; i < len; i++)
        buf->pixels[i] *= ratio;
}

void my_draw_square(framebuffer_t *buf, sfVector2u position, unsigned int size,
    sfColor color)
{
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            my_put_pixel(buf, position.x+x, position.y+y, color);
}

void my_draw_circle(framebuffer_t *buf, sfVector2u position, unsigned int size,
    sfColor *color)
{
    for (int x = 0; x < size*2; x++){
        for (int y = 0; y < size*2; y++){
            if ((pow((double)x-size, 2) + pow((double)y-size, 2)) <=
            pow((double)size, 2)){
                my_put_pixel(buf, x + position.x-size, y +
                position.y-size, *color);
            }
        }
    }
}

int my_draw_line2(framebuffer_t *buf, sfVector2u *vects0, sfVector2u *vects1,
    sfColor color)
{
    float size_x = (float)vects1->x - vects0->x;
    float size_y = (float)vects1->y - vects0->y;
    if (size_y < 0.0){
        vects0 = vects1;
        size_x *= -1;
        size_y *= -1;
    }
    float pente = size_x/size_y;
    float x = 0;
    if (size_y > buf->height)
        return (0);
    for (float y = 0; y < size_y; y++, x += pente){
        my_put_pixel(buf, vects0->x+x, vects0->y+y, color);
    }
}

int my_draw_line(framebuffer_t *buf, sfVector2u *vects0, sfVector2u *vects1,
    sfColor color)
{
    float size_x = (float)vects1->x - vects0->x;
    float size_y = (float)vects1->y - vects0->y;

    if (size_x == 0 && size_y == 0) return (0);
    else if (size_x*size_x > size_y*size_y){
        if (size_x < 0.0){
            vects0 = vects1;
            size_x *= -1;
            size_y *= -1;
        }
        my_draw_line2(buf, vects0, vects1, color);
    } else {
        if (size_y < 0.0){
            vects0 = vects1;
            size_x *= -1;
            size_y *= -1;
        }
        my_draw_line2(buf, vects1, vects0, color);
    }
    return (1);
}
