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

sokoban_t *mv_player(sokoban_t *soko)
{
    pos_t *temp = generate_pos(soko->m);
    pos_t *p = soko->p;

    soko->m[temp->y][temp->x]->svr = soko->m[temp->y][temp->x]->actual;
    soko->m[p->y][p->x]->actual = soko->m[p->y][p->x]->svr;
    soko->m[p->y][p->x]->svr = 'P';
    return (soko);
}

sokoban_t *box_mover(sokoban_t *soko, int mv_y, int mv_x)
{
    pos_t *p = soko->p;

    soko->m[p->y + mv_y][p->x + mv_x]->svr = soko->m[p->y][p->x]->svr;
    soko->m[p->y][p->x]->svr = soko->m[p->y][p->x]->actual;
    soko = mv_player(soko);
    return (soko);
}

sokoban_t *mv_box(sokoban_t *soko)
{
    pos_t *p = soko->p;

    if (soko->get == KEY_LEFT && is_movable_box(soko, 0, -1) == 1)
        soko = box_mover(soko, 0, -1);
    else if (soko->get == KEY_RIGHT && is_movable_box(soko, 0, 1) == 1)
        soko = box_mover(soko, 0, 1);
    else if (soko->get == KEY_UP && is_movable_box(soko, -1, 0) == 1)
        soko = box_mover(soko, -1, 0);
    else if (soko->get == KEY_DOWN && is_movable_box(soko, 1, 0) == 1)
        soko = box_mover(soko, 1, 0);
    else
        soko->p = generate_pos(soko->m);
    return (soko);
}

sokoban_t *change_pos(sokoban_t *soko)
{
    pos_t *temp = generate_pos(soko->m);
    pos_t *p = soko->p;

    if (soko->m[p->y][p->x]->svr == '#') {
        soko->p = temp;
        return (soko);
    } else if (soko->m[p->y][p->x]->svr == 'X') {
        soko = mv_box(soko);
        return (soko);
    }
    if (temp->x != soko->p->x || temp->y != soko->p->y) {
        soko = mv_player(soko);
    }

    return (soko);
}

sokoban_t *get_pos(sokoban_t *soko)
{
    int pressed = getch();
    if (pressed == KEY_UP)
        soko->p->y--;
    else if (pressed == KEY_DOWN)
        soko->p->y++;
    else if (pressed == KEY_RIGHT)
        soko->p->x++;
    else if (pressed == KEY_LEFT)
        soko->p->x--;
    else if (pressed == 'q')
        exit(0);
    soko->get = pressed;
    return (soko);
}