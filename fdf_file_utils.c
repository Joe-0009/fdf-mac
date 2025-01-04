#include "fdf.h"





static int  open_map_file(char *file_name)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit(0);
    return (fd);
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