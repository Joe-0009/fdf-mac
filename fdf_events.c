/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:08 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 18:47:25 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window_x(t_vars *vars)
{
	cleanup_image(vars);
	cleanup_window(vars);
	free_points(vars->dim.height, vars->points);
	exit(0);
	return (0);
}
int	close_window_esc(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		cleanup_image(vars);
		cleanup_window(vars);
		free_points(vars->dim.height, vars->points);
		exit(0);
	}
	return (0);
}


int handle_movement(int keycode, t_vars *vars)
{
    if (keycode == 126)
        move_map(vars->points, vars->map, 0,-20);
    else if (keycode == 125)
        move_map(vars->points, vars->map, 0,20);
    else if (keycode == 123)
        move_map(vars->points, vars->map, -20, 0);
    else if (keycode == 124)
        move_map(vars->points, vars->map, 20, 0);
    else if (keycode == 49)
	{
        vars->map->scale.zoom_factor = 1.1;
        calculate_scale(vars->map);
        parse_map(vars->points, vars->window_name, vars->map);
        iso_points(vars);
	}
    if ((keycode >= 123 && keycode <= 126 )|| keycode == 49)
    {
        cleanup_image(vars);
        create_image(vars);
        main_draw(vars);
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    }
    return (0);
}
int zoom_in_and_out(int keycode, t_vars *vars)
{
    if (keycode == 6)
    {
        update_zoom(vars, 1.1);
        cleanup_image(vars);
        create_image(vars);
        main_draw(vars);
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    }
    else if (keycode == 31)
    {
        update_zoom(vars, 0.9);
        cleanup_image(vars);
        create_image(vars);
        main_draw(vars);
        mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    }
    return (0);
}

int key_handler(int keycode, t_vars *vars)
{
	close_window_esc(keycode, vars);
	handle_movement(keycode, vars);
	zoom_in_and_out(keycode, vars);
	return (0);
}

void	mlx_hooks(t_vars *vars, char *str)
{
	vars->window_name = str;
	mlx_hook(vars->win, 2, 1L << 0, key_handler, vars);
	mlx_hook(vars->win, 17, 0, close_window_x, vars);
	create_image(vars);
}