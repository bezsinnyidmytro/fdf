/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:47:16 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:47:18 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			process_zoom(t_env *env)
{
	int			i;
	int			j;

	i = -1;
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
		{
			env->map[i][j]->x = env->map[i][j]->sx * env->zoom;
			env->map[i][j]->y = env->map[i][j]->sy * env->zoom;
			env->map[i][j]->z = env->map[i][j]->sz * (double)(env->zoom)
				/ 10.0 * (double)env->z_mult;
		}
	}
}

void			process_offset(t_env *env)
{
	int			i;
	int			j;
	int			zoom;

	zoom = 30;
	i = -1;
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
		{
			env->map[i][j]->x += env->x_off * zoom;
			env->map[i][j]->y += env->y_off * zoom;
		}
	}
}

static double	d_to_r(int deg)
{
	return ((double)deg / 180.0 * M_PI);
}

static void		expose_point(t_point *p, t_env *env)
{
	int			tx;
	int			ty;
	int			tz;

	ty = p->y;
	tz = p->z;
	p->y = ty * cos(d_to_r(env->rx)) + tz * sin(d_to_r(env->rx));
	p->z = -ty * sin(d_to_r(env->rx)) + tz * cos(d_to_r(env->rx));
	tx = p->x;
	tz = p->z;
	p->x = tx * cos(d_to_r(env->ry)) + tz * sin(d_to_r(env->ry));
	p->z = -tx * sin(d_to_r(env->ry)) + tz * cos(d_to_r(env->ry));
	tx = p->x;
	ty = p->y;
	p->x = tx * cos(d_to_r(env->rz)) - ty * sin(d_to_r(env->rz)) +
			(WINDOW_W / 2);
	p->y = tx * sin(d_to_r(env->rz)) + ty * cos(d_to_r(env->rz)) +
			(WINDOW_H / 2);
}

void			expose_points(t_env *env)
{
	int			i;
	int			j;

	i = -1;
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
			expose_point(env->map[i][j], env);
	}
}
