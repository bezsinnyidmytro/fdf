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
		env->rx -= 10;
		mlx_clear_window(env->mlx, env->win);
		expose_points(env);
		draw_lines(env);
	}
	if (keycode == KRXR)
	{
		env->rx += 10;
		mlx_clear_window(env->mlx, env->win);
		expose_points(env);
		draw_lines(env);
	}
	if (keycode == KRYL)
	{
		env->ry -= 10;
		mlx_clear_window(env->mlx, env->win);
		expose_points(env);
		draw_lines(env);
	}
	if (keycode == KRYR)
	{
		env->ry += 10;
		mlx_clear_window(env->mlx, env->win);
		expose_points(env);
		draw_lines(env);
	}
	if (keycode == KRZL)
	{
		env->rz -= 10;
		mlx_clear_window(env->mlx, env->win);
		expose_points(env);
		draw_lines(env);
	}
	if (keycode == KRZR)
	{
		env->rz += 10;
		mlx_clear_window(env->mlx, env->win);
		expose_points(env);
		draw_lines(env);
	}
	return (0);
}
