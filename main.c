/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:18 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 18:49:25 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int ac, char **av)
{
    t_vars  vars;
    t_map   map;

    if (ac != 2)
        return (0);
    map = map_dimension(av[1]);
    vars.dim = map.dim;
    vars.map = &map;
    vars.points = points_init(&map);
    if (!vars.points)
        return (0);
    vars.mlx = mlx_init();
    if (!vars.mlx)
        return (0);
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "FDF");
    if (!vars.win)
        return (0);
    
    // Initialize map data
    parse_map(vars.points, av[1], &map);
    calculate_scale(&map);
    apply_projection(vars.points, &map);
    move_map(vars.points, &map, 0, 0);
    
    // Set up hooks and create initial image
    mlx_hooks(&vars, av[1]);
    create_image(&vars);
    main_draw(&vars);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
    
    mlx_loop(vars.mlx);
    return (0);
}