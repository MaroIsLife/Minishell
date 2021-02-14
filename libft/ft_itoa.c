/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:26:55 by mougnou           #+#    #+#             */
/*   Updated: 2019/10/31 16:28:21 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int		count(int n)
{
	int i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	char	*positive(int a, char *p, int n)
{
	a--;
	while (a > 0)
	{
		a--;
		p[a] = n % 10 + '0';
		n = n / 10;
	}
	return (p);
}

static	char	*negative(int a, char *p, unsigned int nb)
{
	p[0] = '-';
	a--;
	while (a > 1)
	{
		a--;
		p[a] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (p);
}

char			*ft_itoa(int n)
{
	int				a;
	char			*p;
	unsigned int	nb;

	if (n >= 0)
	{
		a = count(n) + 1;
		p = malloc(a * sizeof(char));
		if (p == 0)
			return (0);
		positive(a, p, n);
	}
	else if (n < 0)
	{
		nb = (unsigned int)(n * -1);
		a = count(n) + 2;
		p = malloc(a * sizeof(char));
		if (p == 0)
			return (0);
		negative(a, p, nb);
	}
	else
		return (0);
	p[a - 1] = '\0';
	return (p);
}
