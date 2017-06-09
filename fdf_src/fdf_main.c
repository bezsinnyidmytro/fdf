/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:39:00 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/09 16:39:02 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			*brasenham_init(t_point *t0, t_point *t1)
{
	int		*data;

	data = (int *)malloc(sizeof(int) * 5);
	if (!data)
		error_call("Malloc error");
	data[0] = abs(t1->x - t0->x);
	data[1] = t0->x < t1->x ? 1 : -1;
	data[2] = -abs(t1->y - t0->y);
	data[3] = t0->y < t1->y ? 1 : -1;
	data[4] = data[0] + data[2];
	return (data);
}

void		brasenham_line(void *mlx, void *win, t_point t0, t_point t1)
{
	int		*d;
	int		e2;

	d = brasenham_init(&t0, &t1);
	while (1)
	{
		if (is_inwindow(t0.x, t0.y))
			mlx_pixel_put(mlx, win, t0.x, t0.y, t0.color);
		if (t0.x == t1.x && t0.y == t1.y)
			break ;
		e2 = 2 * d[4];
		if (e2 > d[2])
		{
			d[4] += d[2];
			t0.x += d[1];
		}
		if (e2 < d[0])
		{
			d[4] += d[0];
			t0.y += d[3];
		}
	}
	free(d);
}

void		draw_lines(t_env *env)
{
	int		i;
	int		j;

	i = -1;
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
		{
			get_color(env->map[i][j], env->z_mult);
			if (i < env->len_l - 1)
				brasenham_line(env->mlx, env->win, *(env->map[i][j]),
					*(env->map[i + 1][j]));
			if (j < env->len_p - 1)
				brasenham_line(env->mlx, env->win, *(env->map[i][j]),
					*(env->map[i][j + 1]));
		}
	}
}

int			close_x(int keycode, t_env *env)
{
	if (keycode && env)
		ft_printf("");
	exit(0);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		process_file(av[1], &env);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
		put_controls(env);
		mlx_hook(env->win, 2, 3, key_hook, env);
		mlx_hook(env->win, 17, 1L << 17, close_x, env);
		mlx_loop(env->mlx);
	}
	else
		ft_printf("Usage: ./fdf <path to map>\n");
	return (1);
}
