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

float find_angle(float *p1, float *p2)
{
    float x = p2[0] - p1[0];
    float y = p2[1] - p1[1];
    float d = pow(pow(x, 2)+pow(y, 2), 0.5);

    if (d == 0)
        return (0);
    float a = acos(x/d);
    y < 0 ? a *= -1 : 0;
    return (a);
}

struct tempo *init_tempo(float **points)
{
    struct tempo *tmp = malloc(sizeof(struct tempo));
    tmp->n = 0;
    int len = 0;
    for (; points[len]; len++);
    tmp->new_point = malloc(len*sizeof(float *));
    for (int i = 0; points[i]; i++)
        tmp->new_point[i] = malloc(sizeof(float)*3);
    for (int i = 0; points[i]; i++)
        for (int ii = 0; ii < 3; ii++)
            tmp->new_point[i][ii] = points[i][ii];
    tmp->center_tmp = malloc(sizeof(float)*2);
    tmp->point_tmp = malloc(sizeof(float)*2);
    return (tmp);
}

void rotate_axis(struct tempo *tmp, float **points, float *center, float *angle)
{
    int n = tmp->n;
    for (int i = 0; points[i]; i++){
        float dx = tmp->new_point[i][(1+n)%3] - center[(1+n)%3];
        float dy = tmp->new_point[i][(2+n)%3] - center[(2+n)%3];
        float dxy = pow(pow(dx, 2)+pow(dy, 2), 0.5);
        tmp->center_tmp[0] = center[(1+n)%3];
        tmp->center_tmp[1] = center[(2+n)%3];
        tmp->point_tmp[0] = tmp->new_point[i][(1+n)%3];
        tmp->point_tmp[1] = tmp->new_point[i][(2+n)%3];
        float az = find_angle(tmp->center_tmp, tmp->point_tmp);
        tmp->new_point[i][(1+n)%3] += (cos(az+angle[(n)%3]) - cos(az)) * dxy;
        tmp->new_point[i][(2+n)%3] += (sin(az+angle[(n)%3]) - sin(az)) * dxy;
    }
    tmp->n++;
}

float **rotate_points(float **points, float *center, float *angle)
{
    struct tempo *tmp = init_tempo(points);

    rotate_axis(tmp, points, center, angle);
    rotate_axis(tmp, points, center, angle);
    rotate_axis(tmp, points, center, angle);
    free(tmp->center_tmp);
    free(tmp->point_tmp);
    float *p = tmp->new_point;
    free(tmp);
    return (p);
}
