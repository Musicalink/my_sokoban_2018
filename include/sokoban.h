/*
** EPITECH PROJECT, 2018
** CPool_2018
** File description:
** Maxence Carpentier
*/

#ifndef BSQ_H_
#define BSQ_H_

typedef struct my_map {
    char actual;
    char svr;
} my_map_t;

typedef struct pos {
    int x;
    int y;
} pos_t;

typedef struct sokoban {
    my_map_t ***m;
    pos_t *p;
    int get;
} sokoban_t;

char **create_map(char *path);

void my_put_array(my_map_t ***array);

my_map_t ***fill_map_case(my_map_t ***temp, int i, int x, char **map);

my_map_t ***generate_map_struct(char **map);

void initialise_screen(void);

sokoban_t *mv_player(sokoban_t *soko);

sokoban_t *box_mover(sokoban_t *soko, int mv_y, int mv_x);

sokoban_t *mv_box(sokoban_t *soko);

sokoban_t *change_pos(sokoban_t *soko);

sokoban_t *get_pos(sokoban_t *soko);

pos_t *generate_pos(my_map_t ***m);

int is_movable_box(sokoban_t *soko, int add_y, int add_x);

int check_victory(my_map_t ***map);

#endif