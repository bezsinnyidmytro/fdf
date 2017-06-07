#include "fdf.h"

void		brasenham_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;

	dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, 0x00000FF00);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > dy) { err += dy; x0 += sx; }
		if (e2 < dx) { err += dx; y0 += sy; }
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
			if (i < env->len_l - 1)
			{
				brasenham_line(env->mlx, env->win, env->map[i][j]->x, env->map[i][j]->y,
					env->map[i + 1][j]->x, env->map[i + 1][j]->y);
			}
			if (j < env->len_p - 1)
			{
				brasenham_line(env->mlx, env->win, env->map[i][j]->x, env->map[i][j]->y,
					env->map[i][j + 1]->x, env->map[i][j + 1]->y); 
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
		draw_lines(env);
		
		// i = env->len_l - 1;
		// j = -1;
		// while (++j < env->len_p - 1)
		// {
		// 	brasenham_line(env->mlx, env->win, (env->map[i][j]->x), (env->map[i][j]->y),
		// 			(int)(env->map[i][j + 1]->x), (int)(env->map[i][j + 1]->y));
		// }
		// j = env->len_p - 1;
		// i = -1;
		// while (++i < env->len_l - 1)
		// {
		// 	brasenham_line(env->mlx, env->win, (int)(env->map[i][j]->x), (int)(env->map[i][j]->y),
		// 			(int)(env->map[i + 1][j]->x), (int)(env->map[i + 1][j]->y));
		// }

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

// int			main2(int ac, char **av)
// {
// 	void	*mlx;
// 	void	*win;

// 	if (ac > 1 && av[1])
// 	{
// 		mlx = mlx_init();
// 		win = mlx_new_window(mlx, 640, 480, "fdf Brasenhams test");
// 		brasenhem_line(mlx, win, 100, 100, 300, 300);
// 		// mlx_hook(win, 2, 3, key_hook, NULL);
// 		mlx_loop(mlx);
// 		// process_file(av[1], &env);
// 		// free_env(env);
// 		// free(env);
// 	}
// 	else
// 		ft_printf("Usage: ./fdf <path to map>\n");
// 	//sleep(1232343);
// 	return (1);
// }

int			main(int ac, char **av)
{
	main1(ac, av);
	sleep(12323453);
	return (1);
}
