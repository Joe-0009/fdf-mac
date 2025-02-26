/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:46 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/10 14:42:21 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str, t_vars *vars)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]))
			result = result * 10 + str[i++] - '0';
		else
			return (free_points(vars->dim.height ,vars->points), mlx_clear_window(vars->mlx, vars->img), ft_error(),1);
		if (!(((result * sign) <= INT_MAX && (result * sign) >= INT_MIN)))
			return (free_points(vars->dim.height , vars->points), mlx_clear_window(vars->mlx, vars->img), ft_error(),1);
	}
	return (result * sign);
}

void    free_points(int map_height, t_point **points)
{
    int    i;

    i = 0;
    if (points)
    {
        while (i < map_height && points[i])
        {
            free(points[i]);
            points[i] = NULL;
            i++;
        }
        free(points);
        points = NULL;
    }
}
