/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:07:16 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 21:33:22 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				s;
	unsigned long	r;
	unsigned int	i;

	s = 1;
	r = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	if (r > __LONG_MAX__)
		return ((s > 0) ? -1 : 0);
	return (r * s);
}
