#include "fdf.h"

static int	count_p(char **str_arr)
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

void		process_file(char *file_name, t_env **env)
{
	int			fd;
	int			*sizes;
	char		*line;
	char		**str_arr;
	int			i;
	int			j;

	fd = open(file_name, O_RDONLY);

	sizes = check_file(file_name);
	(*env) = init_env(sizes);
	free(sizes);
	ft_printf("Segfault after\n");
	i = -1;
	while (get_next_line(fd, &line) && ++i > -1)
	{
		str_arr = ft_strsplit(line, ' ');
		j = -1;
		while (str_arr[++j])
		{
			(*env)->map[i][j]->sx = (j - (*env)->len_p / 2);
			(*env)->map[i][j]->sy = (i - (*env)->len_l / 2);
			(*env)->map[i][j]->sz = ft_atoi(str_arr[j]);
			//get_color((*env)->map[i][j]);	
		}
		strarr_free(str_arr);
		free(line);
		free(str_arr);
	}
	close(fd);
}
