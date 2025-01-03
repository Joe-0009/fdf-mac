#include "fdf.h"

void    iso_point(t_point *a, t_map *map)
{
    int prev_x;
    int prev_y;

    prev_x = a->x;
    prev_y = a->y;
    a->x = (prev_x - prev_y) * cos(map->scale.iso_angle);
    a->y = -a->z + (prev_x + prev_y) * sin(map->scale.iso_angle);
    a->x += WIDTH * 0.4;
    a->y += HEIGHT / 3;
}

void    iso_points(t_point **points, t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->dim.height)
    {
        j = 0;
        while (j < map->dim.width)
        {
            iso_point(&points[i][j], map);
            j++;
        }
        i++;
    }
}