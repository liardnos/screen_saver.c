/*
** EPITECH PROJECT, 2019
** framebuffer.h
** File description:
** Main for print
*/

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_
#include <SFML/Graphics.h>

struct framebuffer {
    unsigned int width;
    unsigned int height;
    sfUint8 *pixels;
};
typedef struct framebuffer framebuffer_t;

struct linked_list{
    int data;
    struct linked_list *next;
};

//needed for good perf
//for_memory_optimisation
struct f_m_o
{
    float **balls;
    framebuffer_t *buf;
    int window_x;
    int window_y;
    int window_z;
    int balls_nb;
    int balls_nb_max;
    int interact_range;
    int interact_range_sqr;
    int grille_x;
    int grille_y;
    int grille_z;
    struct linked_list ***gri;
    struct linked_list_d ****grille;
    sfVector2u *vc1;
    int sqrt;
    sfVector2u *vc2;
    sfColor *color;
    sfVector2i mouse_vec;
    sfVector2u *cir_pos;
    float *center;
    float *angles;
    float **point;
    float **new_point;
    int i;
    int mod;
};
typedef struct f_m_o f_m_o_t;

struct tempo{
    float *point_tmp;
    float *center_tmp;
    float **new_point;
    int n;
};

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height);
void framebuffer_destroy(framebuffer_t *framebuffer);
void my_put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y,
    sfColor color);
void my_fill_buffer(framebuffer_t *buf, sfColor color);
void my_clear_buffer(framebuffer_t *buf);
void my_blur_buffer(framebuffer_t *buf, float ratio);
void my_draw_square(framebuffer_t *buf, sfVector2u position, unsigned int size,
    sfColor color);
void my_draw_circle(framebuffer_t *buf, sfVector2u position, unsigned int size,
    sfColor *color);
int my_draw_line2(framebuffer_t *buf, sfVector2u *vects0, sfVector2u *vects1,
    sfColor color);
int my_draw_line(framebuffer_t *buf, sfVector2u *vects0, sfVector2u *vects1,
    sfColor color);
void my_draw_lines(framebuffer_t *buf, sfVector2u **vects, int n,
    sfColor color);
void linked_list_append(struct linked_list **begin, int nb);
int linked_list_free(struct linked_list *begin);
int linked_list_len(struct linked_list *begin);
int interact_with_ii(int i, int p, f_m_o_t *fmo);
float rand_2(void);
int physique_for_i(f_m_o_t *fmo, int i);
void put_in_list(f_m_o_t *fmo);
void wall_physique(f_m_o_t *fmo, int i);
void all_i_physique(f_m_o_t *fmo);
void init_fmo2(f_m_o_t *fmo);
f_m_o_t *init_fmo(void);
void user_interaction2(f_m_o_t *fmo, int frame);
void user_interaction(f_m_o_t *fmo, int frame, sfRenderWindow *window);
void free_all(f_m_o_t *fmo, sfSprite *sprite, sfTexture *texture,
    sfRenderWindow *window);
framebuffer_t *framebuffer_create_d(unsigned int width, unsigned int height);
void framebuffer_destroy_d(framebuffer_t *framebuffer);
void my_put_pixel_d(framebuffer_t *framebuffer, unsigned int x, unsigned int y,
    sfColor color);
void my_fill_buffer_d(framebuffer_t *buf, sfColor color);
void my_clear_buffer_d(framebuffer_t *buf);
void my_blur_buffer_d(framebuffer_t *buf, float ratio);
void my_draw_square_d(framebuffer_t *buf, sfVector2u position,
    unsigned int size, sfColor color);
void my_draw_circle_d(framebuffer_t *buf, sfVector2u position,
    float size, sfColor *color);
void linked_list_append_d(struct linked_list_d **begin, int nb);
int linked_list_free_d(struct linked_list_d *begin);
float find_angle(float *p1, float *p2);
struct tempo *init_tempo(float **points);
void rotate_axis(struct tempo *tmp, float **points, float *center,
    float *angle);
float **rotate_points(float **points, float *center, float *angle);
int linked_list_len_d(struct linked_list_d *begin);
void init_fmo2_d(f_m_o_t *fmo);
void init_fmo3(f_m_o_t *fmo);
f_m_o_t *init_fmo_d(void);
void put_in_list_d(f_m_o_t *fmo);
int interact_with_ii_d(f_m_o_t *fmo, int i, int ii);
int physique_for_i2(f_m_o_t *fmo, int x, int y, int z);
int physique_for_i_d(f_m_o_t *fmo, int i);
void sim_type(f_m_o_t *fmo, int i);
void make_event(f_m_o_t *fmo, int frame, sfEvent event, sfRenderWindow *window);
void almost_every_things(f_m_o_t *fmo, int i);
void almost_every_things2(f_m_o_t *fmo, sfRenderWindow *window,
    sfTexture *texture, sfSprite *sprite);
void clean2(f_m_o_t *fmo);
void clean(f_m_o_t *fmo, sfSprite *sprite, sfTexture *texture,
    sfRenderWindow *window);
int ddd_simu(int mod);
int dd_simu(int mod);

#endif
