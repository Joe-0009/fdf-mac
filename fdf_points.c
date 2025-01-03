#include "fdf.h"

static void create_point(t_point *point, char **color_split, t_map *map,
                        int i, int j)
{
    int height;

    height = ft_atoi(color_split[0]);
    point->x = j * map->scale.base;
    point->y = i * map->scale.base;
    point->z = height * map->scale.z_scale;
    if (color_split[1]) 
        point->color = (int)strtol(color_split[1], NULL, 16);
    else 
        point->color = calculate_color(height, &map->height);
}

void    parse_map(t_point **points, char *file_name, t_map *map)
{
    int     fd;
    char    *line;
    char    **split;
    int     i;
    int     j;

    find_height_range(file_name, map);
    calculate_scale(map);
    i = 0;
    fd = open(file_name, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        j = 0;
        split = ft_split(line, ' ');
        while (split[j])
        {
            create_point(&points[i][j], ft_split(split[j], ','), map, i, j);
            j++;
        }
        ft_free_strs(split);
        free(line);
        i++;
    }
    close(fd);
}

void    free_points(t_map *map, t_point **points)
{
    int i;

    i = 0;
    while (i < map->dim.height)
        free(points[i++]);
    free(points);
}

t_point **points_init(t_map *map)
{
    t_point **points;
    int     i;

    points = malloc(map->dim.height * sizeof(t_point *));
    if (!points)
        exit(0);
    i = 0;
    while (i < map->dim.height)
    {
        points[i] = malloc(map->dim.width * sizeof(t_point));
        if (!points[i])
        {
            while (--i >= 0)
                free(points[i]);
            free(points);
            exit(0);
        }
        i++;
    }
    return (points);
}