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

int main(int ac, char **av)
{
    sokoban_t *soko = malloc(sizeof(sokoban_t));
    char **map = create_map(av[1]);
    soko->m = generate_map_struct(map);
    soko->p = generate_pos(soko->m);

    initialise_screen();
    while (check_victory(soko->m) == 0) {
        erase();
        my_put_array(soko->m);
        soko = get_pos(soko);
        soko = change_pos(soko);
    }
    endwin();
    if (check_victory(soko->m) == 1)
        return (0);
    else
        return (1);
}