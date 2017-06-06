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

void		normalize_points(t_env *env)
{
	int		i = -1;
	int		j;
	//int		map_width = env->len_p * XSTEP;
	//int		map_height = env->len_l * YSTEP;

	env->x_off = (WINDOW_W) / 2;
	env->y_off = (WINDOW_H) / 2;

	ft_printf("The map offset is: %i : %i\n", env->x_off, env->y_off);
	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
		{
			env->map[i][j]->x += env->x_off;
			env->map[i][j]->y += env->y_off; 
		}
	}
	ft_printf("The math_pi: %lf\n", M_PI);
}

double		d_to_r(int deg)
{
	return ((double)deg / 180.0 * M_PI);
}

void		expose_point(t_point *p, t_env *env)
{
	int		tx;
	int		ty;
	int		tz;

	int 	rot_x = env->rx;
	int 	rot_y = env->ry;
	int 	rot_z = env->rz;

	if (env)
		ft_printf("");
	tx = p->x - WINDOW_W / 2;
	ty = p->y - WINDOW_H / 2;
	tz = p->z;

	// x
	p->y = WINDOW_H / 2 + ty * cos(d_to_r(rot_x)) + tz * sin(d_to_r(rot_x));
	p->z = -ty * sin(d_to_r(rot_x)) + tz * cos(d_to_r(rot_x));

	// y
	tx = p->x - WINDOW_W / 2;
	ty = p->y - WINDOW_H / 2;
	tz = p->z;
	p->x = WINDOW_W / 2 + tx * cos(d_to_r(rot_y)) + tz * sin(d_to_r(rot_y));
	p->z = -tx * sin(d_to_r(rot_y)) + tz * cos(d_to_r(rot_y));


	//z
	tx = p->x - WINDOW_W / 2;
	ty = p->y - WINDOW_H / 2;
	tz = p->z;
	p->x = WINDOW_W / 2 + tx * cos(d_to_r(rot_z)) - ty * sin(d_to_r(rot_z));
	p->y = WINDOW_H / 2 + tx * sin(d_to_r(rot_z)) + ty * cos(d_to_r(rot_z));

	// env->rx = 0;
	// env->ry = 0;
	// env->rz = 0;
}

void		expose_points(t_env *env)
{
	int		i = -1;
	int		j;

	while (++i < env->len_l)
	{
		j = -1;
		while (++j < env->len_p)
			expose_point(env->map[i][j], env);
	}
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

int			main1(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		process_file(av[1], &env);


		//brasenhem_line(env->mlx, env->win, 100, 100, 300, 300);
		normalize_points(env);
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
