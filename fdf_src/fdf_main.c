#include "fdf.h"

void		brasenhem_line(void *mlx, void *win, int x0, int y0, int x1, int y1)
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

int			main1(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		process_file(av[1], &env);

		brasenhem_line(env->mlx, env->win, 100, 100, 300, 300);

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
