#include "fdf.h"

void		free_env(t_env *env)
{
	int		i;
	int		j;


	if (env->win)
	{
		//free(env->win);
		mlx_destroy_window(env->mlx, env->win);
	}
	if (env->mlx)
		free(env->mlx);

	ft_printf("i: %i, j: %i\n", 2, 2);
	if (env->img)
		free(env->img);
	if (env->cntr)
		free(env->cntr);
	if (env->map)
	{
		i = -1;
		while (++i < env->len_l)
		{
			j = -1;
			while (++j < env->len_p)
			{
				//ft_printf("i: %i, j: %i\n", i, j);
				free(env->map[i][j]);
			}
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
