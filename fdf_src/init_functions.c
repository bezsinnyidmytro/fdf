/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:50:46 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:50:47 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		***init_map(int *sizes)
{
	t_point	***map;
	int		i;
	int		j;

	map = (t_point ***)malloc(sizeof(t_point **) * sizes[0]);
	i = -1;
	while (++i < sizes[0])
	{
		map[i] = (t_point **)malloc(sizeof(t_point *) * sizes[1]);
		j = -1;
		while (++j < sizes[1])
			map[i][j] = (t_point *)malloc(sizeof(t_point));
	}
	return (map);
}

int			calc_zoom(int *sizes)
{
	int		max_size;

	max_size = (sizes[0] > sizes[1]) ? sizes[0] : sizes[1];
	if (max_size >= 500)
		return (1);
	else if (max_size >= 250)
		return (2);
	else if (max_size >= 100)
		return (4);
	else if (max_size >= 50)
		return (8);
	else if (max_size >= 25)
		return (16);
	else
		return (32);
}

t_env		*init_env(int *sizes)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		perror("Error.");
	env->mlx = mlx_init();
	if (!env->mlx)
		perror("Error.");
	env->win = mlx_new_window(env->mlx, WINDOW_W, WINDOW_H, "42fdf");
	if (!env->win)
		perror("Error.");
	env->img = NULL;
	env->rx = ROT_X;
	env->ry = ROT_Y;
	env->rz = ROT_Z;
	env->zoom = calc_zoom(sizes);
	env->z_mult = 1;
	env->cntr = NULL;
	env->map = init_map(sizes);
	env->len_l = sizes[0];
	env->len_p = sizes[1];
	env->x_off = 0;
	env->y_off = 0;
	return (env);
}
