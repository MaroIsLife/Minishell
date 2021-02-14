/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:53:18 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 11:58:34 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*s1;

	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*s1 == (unsigned char)c)
		{
			return (s1);
		}
		s1++;
		i++;
	}
	return (0);
}
