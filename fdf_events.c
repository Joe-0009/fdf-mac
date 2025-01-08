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
	if (keycode == 65307)
	{
		cleanup_image(vars);
		cleanup_window(vars);
		free_points(vars->dim.height, vars->points);
		exit(0);
	}
	return (0);
}


int	move_up(int keycode, t_vars *vars)
{
	if (keycode == 126)
	{
		cleanup_image(vars);
		create_image(vars);
		move_map(vars->points, vars->map, 20);
		main_draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	return (0);
}

int key_handler(int keycode, t_vars *vars)
{
	close_window_esc(keycode, vars);
	move_up(keycode, vars);
	return (0);
}

void	mlx_hooks(t_vars *vars, char *str)
{
	vars->window_name = str;
	mlx_hook(vars->win, 2, 1L << 0, key_handler, vars);
	mlx_hook(vars->win, 17, 0, close_window_x, vars);
	create_image(vars);
}