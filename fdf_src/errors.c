#include "fdf.h"

void		error_call(char *message)
{
	ft_printf("%s", KRED);
	ft_printf("Error. %s.\n", message);
	ft_printf("%s", KNRM);
	sleep(1232354);
	exit(1);
}
