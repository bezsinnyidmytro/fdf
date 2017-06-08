/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:58:27 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:58:28 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		redraw_window(int is_control_key, t_env *env)
{
	if (is_control_key)
	{
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
}

static void	key_hook_add(int keycode, t_env *env, int *is_ck)
{
	if (keycode == KRZR && (*is_ck = 1))
		env->rz = (env->rz + 10) % 360;
	if (keycode == ZIN && (*is_ck = 1))
	{
		env->zoom += 1;
		ft_printf("Zoom is: %i\n", env->zoom);
	}
	if (keycode == ZOUT && (*is_ck = 1))
	{
		env->zoom = (env->zoom == 1) ? 1 : (env->zoom - 1);
		ft_printf("Zoom is: %i\n", env->zoom);
	}
	if (keycode == ZUP && (*is_ck = 1))
		env->z_mult += 1;
	if (keycode == ZDOWN && (*is_ck = 1))
		env->z_mult -= 1;
	if (keycode == MVL && (*is_ck = 1))
		env->x_off--;
	if (keycode == MVR && (*is_ck = 1))
		env->x_off++;
	if (keycode == MVD && (*is_ck = 1))
		env->y_off++;
	if (keycode == MVU && (*is_ck = 1))
		env->y_off--;
}

int			key_hook(int keycode, t_env *env)
{
	int		is_control_key;

	is_control_key = 0;
	ft_printf("Key code is: %i\n", keycode);
	if (keycode == KESC && (is_control_key = 1))
	{
		mlx_destroy_window(env->mlx, env->win);
		env->win = NULL;
		free_env(env);
		//sleep(12334);
		exit(0);
	}
	if (keycode == KRXL && (is_control_key = 1))
		env->rx = (env->rx - 10) % 360;
	if (keycode == KRXR && (is_control_key = 1))
		env->rx = (env->rx + 10) % 360;
	if (keycode == KRYL && (is_control_key = 1))
		env->ry = (env->ry - 10) % 360;
	if (keycode == KRYR && (is_control_key = 1))
		env->ry = (env->ry + 10) % 360;
	if (keycode == KRZL && (is_control_key = 1))
		env->rz = (env->rz - 10) % 360;
	key_hook_add(keycode, env, &is_control_key);
	redraw_window(is_control_key, env);
	return (0);
}
