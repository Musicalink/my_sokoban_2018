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

void my_put_array(my_map_t ***array)
{
    for (int y = 0; array[y] != NULL; y++) {
        for (int x = 0; array[y][x] != NULL; x++)
            if (array[y][x]->actual == array[y][x]->svr) {
                printw("%c", array[y][x]->actual);
            } else {
                printw("%c", array[y][x]->svr);
            }
        printw("\n");
    }
}

char **create_map(char *path)
{
    int fd = open(path, O_RDONLY);
    char *buff;
    char **res;
    struct stat *info = malloc(sizeof(struct stat));
    int size;

    if (fd == -1)
        exit(84);
    stat(path, info);
    size = (int)(info->st_size);
    if (size <= 0)
        exit(84);
    buff = malloc(sizeof(char) * (size + 1));
    read(fd, buff, size);
    close(fd);
    free(info);
    res = my_str_to_word_array(buff);
    free(buff);
    return (res);
}

my_map_t ***fill_map_case(my_map_t ***temp, int i, int x, char **map)
{
    temp[i][x] = malloc(sizeof(my_map_t));
    if (map[i][x] == ' ' || map[i][x] == '#' || map[i][x] == 'O') {
        temp[i][x]->actual = map[i][x];
        temp[i][x]->svr = map[i][x];
    } else {
        temp[i][x]->actual = ' ';
        temp[i][x]->svr = map[i][x];
    }
    return (temp);
}

my_map_t ***generate_map_struct(char **map)
{
    my_map_t ***temp = malloc(sizeof(my_map_t * *) * my_tablen(map) + 1);
    int x;
    int i;

    for (i = 0; i < my_tablen(map); i++) {
        temp[i] = malloc(sizeof(my_map_t * ) * my_strlen(map[i]) + 1);
        for (x = 0; x < my_strlen(map[i]); x++)
            temp = fill_map_case(temp, i, x, map);
        temp[i][x] = NULL;
    }
    temp[i] = NULL;
    return (temp);
}

void initialise_screen(void)
{
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, 1);
}