#include "fdf.h"

void    iso_point(t_point *a, t_map *map)
{
    int prev_x;
    int prev_y;
    static t_bounds bounds = {INT_MAX, INT_MIN, INT_MAX, INT_MIN};  // Track boundaries
    
    prev_x = a->x;
    prev_y = a->y;
    
    // Calculate isometric projection
    a->x = (prev_x - prev_y) * cos(map->scale.iso_angle);
    a->y = -a->z + (prev_x + prev_y) * sin(map->scale.iso_angle);
    
    // Track min and max before centering
    if (a->x < bounds.min_x) bounds.min_x = a->x;
    if (a->x > bounds.max_x) bounds.max_x = a->x;
    if (a->y < bounds.min_y) bounds.min_y = a->y;
    if (a->y > bounds.max_y) bounds.max_y = a->y;
    
    // Debug print for first and last points
    printf("Point at (%d,%d) projected to (%d,%d)\n", prev_x, prev_y, a->x, a->y);
    printf("Current bounds: x[%d,%d] y[%d,%d]\n", bounds.min_x, bounds.max_x, bounds.min_y, bounds.max_y);
    
    // Calculate center offset based on actual width
    int map_width = bounds.max_x - bounds.min_x;
    int center_offset_x = (WIDTH - map_width) / 2;
    
    a->x += center_offset_x;
    a->y += HEIGHT / 2;
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