#include "fdf.h"

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
	if (!env)
		perror("Error.");
	env->mlx = mlx_init();
	if (!env->mlx)
		perror("Error.");
	env->win = mlx_new_window(env->mlx, WINDOW_W, WINDOW_H, "42fdf");
	if (!env->win)
		perror("Error.");
	env->img = NULL;
	env->rx = ROT_X;
	env->ry = ROT_Y;
	env->rz = ROT_Z;
	env->zoom = ZOOM;
	env->z_mult = 1.0;
	env->cntr = NULL;
	env->map = init_map(sizes);
	env->len_l = sizes[0];
	env->len_p = sizes[1];
	return (env);
}
