/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:57:06 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:57:10 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	*parse_size(int lines, int points)
{
	int		*sizes;

	sizes = (int *)malloc(sizeof(int) * 2);
	sizes[0] = lines;
	sizes[1] = points;
	return (sizes);
}

static int	*check_map(char *file_name)
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
		str_arr = ft_strsplit(line, ' ');
		if (l_count > 1)
			line_check(p_count, str_arr, line);
		p_count = count_p(str_arr);
		free(line);
		strarr_free(str_arr);
		free(str_arr);
	}
	close(fd);
	return (parse_size(l_count, p_count));
}

static int	*check_file(char *file_name)
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

void		fill_env(int fd, t_env **env)
{
	int		i;
	int		j;
	char	*line;
	char	**str_arr;

	i = -1;
	while (get_next_line(fd, &line) && ++i > -1)
	{
		str_arr = ft_strsplit(line, ' ');
		j = -1;
		while (str_arr[++j])
		{
			if (!ft_isdss(str_arr[j][0]))
				error_call("Map error. Bad character");
			(*env)->map[i][j]->sx = (j - (*env)->len_p / 2);
			(*env)->map[i][j]->sy = (i - (*env)->len_l / 2);
			(*env)->map[i][j]->sz = ft_atoi(str_arr[j]);
		}
		strarr_free(str_arr);
		free(line);
		free(str_arr);
	}
}

void		process_file(char *file_name, t_env **env)
{
	int		fd;
	int		*sizes;

	fd = open(file_name, O_RDONLY);
	sizes = check_file(file_name);
	(*env) = init_env(sizes);
	free(sizes);
	fill_env(fd, env);
	close(fd);
}
