/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbezsinn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 17:23:20 by dbezsinn          #+#    #+#             */
/*   Updated: 2017/06/05 17:23:22 by dbezsinn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_checkstr(const char *str, int (*check_f)(int))
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!((*check_f)(*str)))
			return (0);
		str++;
	}
	return (1);
}
