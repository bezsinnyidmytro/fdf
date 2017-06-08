#include "fdf.h"

// Problems with zoom+offset

void		get_color(t_point *p, int z_mult)
{
	int		dmn;

	dmn = p->sz * z_mult;
	if (dmn < -10)
	{
		if (dmn >= -250)
			p->color = (0x006600 + (-dmn));
		else
			p->color = (0x0066FF);
	}
	else if (dmn > 10)
	{
		if (dmn <= 250)
			p->color = (0x006600 + ((dmn) << 16));
		else
			p->color = (0xFF6600);
	}
	else
		p->color = (0x006600);
	// ft_printf("Z is: %i\n", p->z);
}

void		brasenham_line(void *mlx, void *win, t_point t0, t_point t1)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(t1.x - t0.x);
	sx = t0.x < t1.x ? 1 : -1;
	dy = -abs(t1.y - t0.y);
	sy = t0.y < t1.y ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(mlx, win, t0.x, t0.y, t0.color);
		if (t0.x == t1.x && t0.y == t1.y)
			break;
		e2 = 2 * err;
		if (e2 > dy)
		{
			err += dy;
			t0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			t0.y += sy;
		}
	}
}

// void		normalize_points(t_env *env)
// {
// 	int		i = -1;
// 	int		j;
// 	//int		map_width = env->len_p * XSTEP;
// 	//int		map_height = env->len_l * YSTEP;

// 	env->x_off = (WINDOW_W) / 2;
// 	env->y_off = (WINDOW_H) / 2;

// 	ft_printf("The map offset is: %i : %i\n", env->x_off, env->y_off);
// 	while (++i < env->len_l)
// 	{
// 		j = -1;
// 		while (++j < env->len_p)
// 		{
// 			env->map[i][j]->x = env->map[i][j]->sx + env->x_off;
// 			env->map[i][j]->y = env->map[i][j]->sy + env->y_off;
// 			env->map[i][j]->z = env->map[i][j]->sz; 
// 		}
// 	}
// 	ft_printf("The math_pi: %lf\n", M_PI);
// }

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
			{
				brasenham_line(env->mlx, env->win, *(env->map[i][j]), *(env->map[i + 1][j]));
			}
			if (j < env->len_p - 1)
			{
				brasenham_line(env->mlx, env->win, *(env->map[i][j]), *(env->map[i][j + 1])); 
			}
		}
	}
}

int			close_x(int keycode, t_env *env)
{
	if (keycode)
		ft_printf("");
	//mlx_destroy_window(env->mlx, env->win);
	env->win = NULL;
	free_env(env);
	exit(0);
}

int			main1(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		process_file(av[1], &env);
		//ft_printf("X %i, Y %i, Z %i\n", env->map[1][1]->sx, env->map[1][1]->sy, env->map[1][1]->sz);
		//brasenhem_line(env->mlx, env->win, 100, 100, 300, 300);
		//normalize_points(env);
		process_zoom(env);
		expose_points(env);
		process_offset(env);
		draw_lines(env);

		mlx_hook(env->win, 2, 3, key_hook, env);
		mlx_hook(env->win, 17, 1L << 17, close_x, env);
		mlx_loop(env->mlx);
		//free(env);
	}
	else
		ft_printf("Usage: ./fdf <path to map>\n");
	sleep(1232343);
	return (1);
}

int			main(int ac, char **av)
{
	main1(ac, av);
	sleep(12323453);
	return (1);
}
