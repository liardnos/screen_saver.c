/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** Main for print
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "2d_screen/framebuffer.h"

const char *error =
"/my_screensaver: bad arguments: 0 given but 1 is required\nretry with -h\n";

const char *h_help =
"rendering animation with CSFML\n\n"
"USAGE\n"
"   ./my_screensaver ID\n\n"
"OPTION\n"
"   -d      print description of all animation\n"
"   -h      print the usage\n";

const char *d_text =
"1: 2D particle simulation\n"
"2: interaction force rendering\n"
"3: 3D simulation with 20000 particle (Sphere)\n"
"4: 3D simulation with 20000 particle (Cube)\n";

int my_strlen(const char *str)
{
    int i = 0;
    for (; str[i]; i++);
    return (i);
}

int main(int ac, char **av)
{
    if (ac != 2) write(1, error, my_strlen(error));
    if (ac != 2) exit(84);

    if (av[1][1] == 'd') write(1, d_text, my_strlen(d_text));
    if (av[1][1] == 'h') write(1, h_help, my_strlen(h_help));

    if (av[1][0] == '1') dd_simu(0);
    if (av[1][0] == '2') dd_simu(1);
    if (av[1][0] == '3') ddd_simu(0);
    if (av[1][0] == '4') ddd_simu(1);
}
