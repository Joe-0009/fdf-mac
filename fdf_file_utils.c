#include "fdf.h"

static void free_and_null(void **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

static void exit_with_error(char *message)
{
    ft_putendl_fd(message, 2);
    exit(EXIT_FAILURE);
}

static int  open_map_file(char *file_name)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_with_error("Failed to open file");
    return (fd);
}

void    ft_free_strs(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
        free(strs[i++]);
    free(strs);
}

t_map   map_dimension(char *file_name)
{
    t_map   map;
    int     fd;
    char    *line;
    int     height;

    height = 0;
    fd = open_map_file(file_name);
    while ((line = get_next_line(fd)))
    {
        if (height == 0)
            map.dim.width = ft_words_count(line, ' ');
        height++;
        free(line);
    }
    close(fd);
    map.dim.height = height;
    return (map);
}