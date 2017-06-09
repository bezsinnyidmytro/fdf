/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:49:26 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:49:28 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		free_env(t_env *env)
{
	int		i;
	int		j;

	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->mlx)
		free(env->mlx);
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
		to_free = *str_arr;
		free(to_free);
		str_arr++;
	}
}
