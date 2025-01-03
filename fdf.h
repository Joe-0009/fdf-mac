#ifndef FDF_H
# define FDF_H


# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1200
# define HEIGHT 800

typedef struct s_dimensions
{
    int     width;
    int     height;
}   t_dimensions;

typedef struct s_scale
{
    float   base;
    float   z_scale;
    float   iso_angle;
}   t_scale;

typedef struct s_offset
{
    int     x;
    int     y;
}   t_offset;

typedef struct s_height_range
{
    int     min;
    int     max;
}   t_height_range;

typedef struct s_map
{
    t_dimensions    dim;
    t_scale         scale;
    t_offset        offset;
    t_height_range  height;
}   t_map;

typedef struct s_point
{
    int     x;
    int     y;
    int     z;
    int     color;
}   t_point;

typedef struct s_image
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_image;

typedef struct s_vars
{
    void    *mlx;
    void    *win;
    char    *window_name;
    t_image img;
}   t_vars;



# define ERR_MLX_INIT "Error initializing mlx"
# define ERR_WIN_CREATE "Error creating window"
# define ERR_IMG_CREATE "Error creating image"



void    cleanup_mlx(t_vars *vars);
void    cleanup_window(t_vars *vars);
void    handle_init_error(char *message, t_vars *vars);
void    init_fdf(t_vars *vars);
void    create_image(t_vars *vars);

// File operations
void        ft_free_strs(char **strs);
t_map       map_dimension(char *file_name);

// Height processing
int calculate_color(int height, t_height_range *range);
void        calculate_scale(t_map *map);
void        find_height_range(char *file_name, t_map *map);

// Point management
void        parse_map(t_point **points, char *file_name, t_map *map);
void        free_points(t_map *map, t_point **points);
t_point     **points_init(t_map *map);

// Transformation
void        iso_point(t_point *a, t_map *map);
void        iso_points(t_point **points, t_map *map);

// Utility functions
int         ft_words_count(char const *s, char c);
char        **ft_split(char const *s, char c);
int         ft_atoi(const char *str);

// Pixel operations
void    put_pixel(t_vars *vars, int x, int y, int color);
int     interpolate_color(int color1, int color2, float fraction);

// Line drawing
void    draw_line_low_slope(t_vars *vars, int dx, int dy, t_point *a, t_point *b);
void    draw_line_high_slope(t_vars *vars, int dx, int dy, t_point *a, t_point *b);
void    draw_line(t_vars *vars, t_point a, t_point b);

// Main drawing
void    main_draw(t_vars *vars, t_point **points, t_map *map);

// Event handling
int         close_window_esc(int keycode, t_vars *vars);
int         close_window_x(t_vars *vars);
void        mlx_hooks(t_vars *vars, char *str);

#endif