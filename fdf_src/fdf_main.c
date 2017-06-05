#include "fdf.h"

void		error_call(char *message)
{
	ft_printf("%s", KRED);
	ft_printf("Error. %s.\n", message);
	ft_printf("%s", KNRM);
	sleep(1232354);
	exit(1);
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

void		check_map(char *file_name)
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
}

void		check_file(char *file_name)
{
	int		fd;
	char	test;

	if ((fd = open(file_name, O_DIRECTORY)) > 0)
		error_call("File name is required, directory name is provided");
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || (read(fd, &test, 1) < 1))
		error_call("Map error. File doesn't exist or is empty");
	close(fd);
	check_map(file_name);
}

void		process_file(char *file_name)
{
	int		fd;

	check_file(file_name);
	fd = open(file_name, O_RDONLY);

}

int			main(int ac, char **av)
{
	if (ac > 1)
		process_file(av[1]);
	else
		ft_printf("Usage: ./fdf <path to map>\n");
	sleep(1232343);
	return (1);
}
