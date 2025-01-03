#include "fdf.h"

static void process_height(char *str, t_height_range *height)
{
    int current_height;

    current_height = ft_atoi(str);
    if (current_height < height->min)
        height->min = current_height;
    if (current_height > height->max)
        height->max = current_height;
} 

void    find_height_range(char *file_name, t_map *map)
{
    int     fd;
    char    *line;
    char    **split;
    char    **color_split;

    map->height.min = INT_MAX;
    map->height.max = INT_MIN;
    fd = open(file_name, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        split = ft_split(line, ' ');
        while (*split)
        {
            color_split = ft_split(*split, ',');
            process_height(color_split[0], &map->height);
            ft_free_strs(color_split);
            split++;
        }
        free(line);
    }
    close(fd);
}

int calculate_color(int height, t_height_range *range)
{
    float height_percent;

    if (height == 0)
        return (0x0000FF);
    height_percent = (float)(height - range->min) /
                    (range->max - range->min + 0.1);
    return (0xFFFFFF - (int)(height_percent * 0x00FFFF));
}

void    calculate_scale(t_map *map)
{
    float   max_projected_width;
    float   height_range;
    float   scale_x;
    float   scale_y;
    float   height_factor;

    max_projected_width = map->dim.width + map->dim.height;
    height_range = map->height.max - map->height.min;
    if (height_range > 0)
    {
        if (height_range > map->dim.width)
            height_factor = (float)map->dim.width / height_range;
        else if (height_range < map->dim.width / 4)
            height_factor = 2.0;
        else
            height_factor = 1.0;
    }
    else
        height_factor = 1.0;
    scale_x = WIDTH / (max_projected_width * 2);
    scale_y = HEIGHT / ((max_projected_width * sin(0.523599)) +
             (height_range * height_factor));
    map->scale.base = (scale_x < scale_y) ? scale_x : scale_y;
    map->scale.z_scale = map->scale.base * height_factor;
    map->scale.iso_angle = 0.523599;
}