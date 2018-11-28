/*
** EPITECH PROJECT, 2018
** CPool_2018
** File description:
** Maxence Carpentier
*/

#include "my.h"
#include "sokoban.h"
#include <stdlib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

pos_t *generate_pos(my_map_t ***m)
{
    pos_t *temp = malloc(sizeof(pos_t));

    for (int y = 0; m[y] != NULL; y++)
        for (int x = 0; m[y][x] != NULL; x++)
            if (m[y][x]->svr == 'P') {
                temp->x = x;
                temp->y = y;
                break;
            }
    return (temp);
}

int is_movable_box(sokoban_t *soko, int add_y, int add_x)
{
    if (soko->m[soko->p->y + add_y][soko->p->x + add_x]->svr == 'X')
        return (0);
    else if (soko->m[soko->p->y + add_y][soko->p->x + add_x]->svr == '#')
        return (0);
    return (1);
}

int check_victory(my_map_t ***map)
{
    for (int y = 0; map[y] != NULL; y++)
        for (int x = 0; map[y][x] != NULL; x++) {
            if (map[y][x]->actual == 'O' && map[y][x]->svr != 'X')
                return (0);
        }
    return (1);
}