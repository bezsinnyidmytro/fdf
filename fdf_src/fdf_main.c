#include "fdf.h"
#include <math.h>
#include <mlx.h>

void		error_call(char *message)
{
	ft_printf("%s", KRED);
	ft_printf("Error. %s.\n", message);
	ft_printf("%s", KNRM);
	sleep(1232354);
	exit(1);
}

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

void		free_env(t_env *env)
{
	int		i;
	int		j;

	// if (env->win)
	// {
	// 	//free(env->win);
	// 	mlx_destroy_window(env->mlx, env->win);
	// }
	// if (env->mlx)
	// 	free(env->mlx);
	// if (env->img)
	// 	free(env->img);
	// if (env->cntr)
	// 	free(env->cntr);
	if (env->map)
	{
		i = -1;
		while (++i < env->len_l)
		{
			j = -1;
			while (++j < env->len_p)
				free(env->map[i][j]);
			free(env->map[i]);
		}
		free(env->map);
	}
}

void		strarr_free(char **str_arr)
{
	char	*to_free;

	if (!str_arr)
		return ;
	while (*str_arr)
	{
		//printf("Freed\n");
		to_free = *str_arr;
		free(to_free);
		str_arr++;
	}
	//free(str_arr);
}

int			count_p(char **str_arr)
{
	int		p_c;

	p_c = 0;
	if (!str_arr)
		return (p_c);
	while (*str_arr)
	{
		p_c++;
		str_arr++;
	}
	return (p_c);
}

int			*parse_size(int lines, int points)
{
	int		*sizes;

	sizes = (int *)malloc(sizeof(int) * 2);
	sizes[0] = lines;
	sizes[1] = points;
	return (sizes);
}

int			*check_map(char *file_name)
{
	int		fd;
	char	**str_arr;
	int		p_count;
	int		l_count;
	char	*line;

	l_count = 0;
	p_count = 0;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		l_count++;
		if (!ft_checkstr(line, &ft_isdss))
		{
			free(line);
			error_call("Map error. Bad character");
		}
		str_arr = ft_strsplit(line, ' ');
		if (l_count > 1)
		{
			if (p_count != count_p(str_arr))
			{
				free(line);
				strarr_free(str_arr);
				free(str_arr);
				error_call("Map error. Inconsistent number of points");	
			}
		}
		p_count = count_p(str_arr);
		free(line);
		strarr_free(str_arr);
		free(str_arr);
	}
	close(fd);
	return (parse_size(l_count, p_count));
}

int			*check_file(char *file_name)
{
	int		fd;
	char	test;

	if ((fd = open(file_name, O_DIRECTORY)) > 0)
		error_call("File name is required, directory name is provided");
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || (read(fd, &test, 1) < 1))
		error_call("Map error. File doesn't exist or is empty");
	close(fd);
	return (check_map(file_name));
}

t_point		***init_map(int *sizes)
{
	// Check for number of lines 1 and colls 1 !!!!!!!!!
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

t_env		*init_env(int *sizes)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	// env->mlx = mlx_init();
	// env->win = mlx_new_window(env->mlx, WINDOW_W, WINDOW_H, "42fdf");
	// env->img = NULL;
	// env->cntr = NULL;
	env->map = init_map(sizes);
	env->len_l = sizes[0];
	env->len_p = sizes[1];
	return (env);
}

void		process_file(char *file_name, t_env **env)
{
	//int		fd;
	int		*sizes;

	sizes = check_file(file_name);
	(*env) = init_env(sizes);
	free(sizes);

	int 	i = -1;
	int		j;
	while (++i < (*env)->len_l)
	{
		j = -1;
		while (++j < (*env)->len_p)
		{
			(*env)->map[i][j]->x = (double)(j + 1) * XSTEP;
			(*env)->map[i][j]->y = (double)(i + 1) * YSTEP;
			(*env)->map[i][j]->z = 42.0;
		}
	}

	ft_printf("X: %.1lf, Y: %.1lf, Z: %.1lf\t", (*env)->map[0][0]->x, (*env)->map[0][0]->y, (*env)->map[0][0]->z);		// leaks in PRINTF with lf conversion
	// i = -1;
	// while (++i < (*env)->len_l)
	// {
	// 	j = -1;
	// 	while (++j < (*env)->len_p)
	// 	{
	// 		ft_printf("X: %.1lf, Y: %.1lf, Z: %.1lf\t", (*env)->map[i][j]->x, (*env)->map[i][j]->y, (*env)->map[i][j]->z);
	// 	}
	// 	ft_printf("\n");
	// }
	//fd = open(file_name, O_RDONLY);
}

int			main1(int ac, char **av)
{
	t_env	*env;

	if (ac > 1)
	{
		process_file(av[1], &env);
		free_env(env);
		free(env);
	}
	else
		ft_printf("Usage: ./fdf <path to map>\n");
	sleep(1232343);
	return (1);
}

int			main2(int ac, char **av)
{
	void	*mlx;
	void	*win;

	if (ac > 1 && av[1])
	{
		mlx = mlx_init();
		win = mlx_new_window(mlx, 640, 480, "fdf Brasenhams test");
		brasenhem_line(mlx, win, 100, 100, 300, 300);
		// mlx_hook(win, 2, 3, key_hook, NULL);
		mlx_loop(mlx);
		// process_file(av[1], &env);
		// free_env(env);
		// free(env);
	}
	else
		ft_printf("Usage: ./fdf <path to map>\n");
	//sleep(1232343);
	return (1);
}

int			main(int ac, char **av)
{
	main1(ac, av);
	sleep(12323453);
	return (1);
}
