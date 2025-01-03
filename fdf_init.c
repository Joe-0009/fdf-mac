#include "fdf_init.h"

static void    cleanup_mlx(t_vars *vars)
{
    if (vars->mlx)
    {
        free(vars->mlx);
        vars->mlx = NULL;
    }
}

static void    cleanup_window(t_vars *vars)
{
    if (vars->win)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        vars->win = NULL;
    }
    cleanup_mlx(vars);
}

static void    handle_init_error(char *message, t_vars *vars)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void    init_fdf(t_vars *vars)
{
    vars->mlx = mlx_init();
    if (!vars->mlx)
        handle_init_error(ERR_MLX_INIT, vars);

    vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, vars->window_name);
    if (!vars->win)
    {
        cleanup_mlx(vars);
        handle_init_error(ERR_WIN_CREATE, vars);
    }
}

void    create_image(t_vars *vars)
{
    vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
    if (!vars->img.img)
    {
        cleanup_window(vars);
        handle_init_error(ERR_IMG_CREATE, vars);
    }

    vars->img.addr = mlx_get_data_addr(vars->img.img,
                                    &vars->img.bits_per_pixel,
                                    &vars->img.line_length,
                                    &vars->img.endian);
    if (!vars->img.addr)
    {
        mlx_destroy_image(vars->mlx, vars->img.img);
        cleanup_window(vars);
        handle_init_error("Error getting image data address", vars);
    }
}