/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:45:13 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/07 11:45:16 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		error_call(char *message)
{
	ft_printf("%s", KRED);
	ft_printf("Error. %s.\n", message);
	ft_printf("%s", KNRM);
	exit(1);
}

void		get_color(t_point *p, int z_mult)
{
	int		dmn;

	dmn = p->sz * z_mult;
	if (dmn < -10)
	{
		if (dmn >= -250)
			p->color = (0x006600 + (-dmn));
		else
			p->color = (0x0066FF);
	}
	else if (dmn > 10)
	{
		if (dmn <= 250)
			p->color = (0x006600 + ((dmn) << 16));
		else
			p->color = (0xFF6600);
	}
	else
		p->color = (0x006600);
}

int			is_inwindow(int x, int y)
{
	if (x > WINDOW_W || y > WINDOW_H)
		return (0);
	return (1);
}
