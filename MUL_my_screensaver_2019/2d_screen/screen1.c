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

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *buf = malloc(sizeof(struct framebuffer));

    buf->width = width;
    buf->height = height;
    buf->pixels = malloc(width*height*sizeof(sfUint8)*4);
    memset(buf->pixels, 0, width*height*sizeof(sfUint8)*4);
    return (buf);
}

void framebuffer_destroy(framebuffer_t *framebuffer)
{
    free(framebuffer->pixels);
    free(framebuffer);
}

void my_put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y,
    sfColor color)
{
    if (x >= 0 && x < framebuffer->width && y >= 0 && y < framebuffer->height){
        framebuffer->pixels[(y*framebuffer->width + x)*4] = color.r;
        framebuffer->pixels[(y*framebuffer->width + x)*4 + 1] = color.g;
        framebuffer->pixels[(y*framebuffer->width + x)*4 + 2] = color.b;
        framebuffer->pixels[(y*framebuffer->width + x)*4 + 3] = color.a;
    }
}

void my_fill_buffer(framebuffer_t *buf, sfColor color)
{
    for (int x = 0; x < buf->width; x++)
        for (int y = 0; y < buf->height; y++)
            my_put_pixel(buf, x, y, color);
}

void my_clear_buffer(framebuffer_t *buf)
{
    memset(buf->pixels, 0, buf->width*buf->height*sizeof(sfUint8)*4);
}
