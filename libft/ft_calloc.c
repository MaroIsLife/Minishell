/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:47:55 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 19:50:58 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ftt_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	s1 = (unsigned char*)s;
	while (i < n)
	{
		s1[i] = 0;
		i++;
	}
}

void			*ft_calloc(size_t n, size_t size)
{
	void *i;

	i = malloc(n * size);
	if (i == NULL)
		return (0);
	else
	{
		ftt_bzero(i, n * size);
		return (i);
	}
}
