#include "fdf.h"

int			key_hook(int keycode, t_env *env)
{
	ft_printf("Key code is: %i\n", keycode);
	if (keycode == KESC)
	{
		mlx_destroy_window(env->mlx, env->win);
		env->win = NULL;
		free_env(env);
		exit(0);
	}
	if (keycode == KRXL)
	{
		env->rx = (env->rx - 10) % 360;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == KRXR)
	{
		env->rx = (env->rx + 10) % 360;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == KRYL)
	{
		env->ry = (env->ry - 10) % 360;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == KRYR)
	{
		env->ry = (env->ry + 10) % 360;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == KRZL)
	{
		env->rz = (env->rz - 10) % 360;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == KRZR)
	{
		env->rz = (env->rz + 10) % 360;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == ZIN)
	{
		env->zoom += 1;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == ZOUT)
	{
		env->zoom = (env->zoom == 1) ? 1 : (env->zoom - 1);
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == ZUP)
	{
		env->z_mult += 1;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == ZDOWN)
	{
		env->z_mult -= 1;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == MVL)
	{
		env->x_off--;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == MVR)
	{
		env->x_off++;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == MVD)
	{
		env->y_off++;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	if (keycode == MVU)
	{
		env->y_off--;
		mlx_clear_window(env->mlx, env->win);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);
	}
	return (0);
}
