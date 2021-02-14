/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:11:31 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 21:52:47 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			b;
	size_t			i;
	size_t			c;
	size_t			f;

	b = 0;
	i = 0;
	c = ft_strlen(src);
	if (dst == 0 && size == 0)
		return (c);
	b = ft_strlen(dst);
	if (size <= b)
		return (size + c);
	f = b;
	while (i < size - b - 1 && src[i] != '\0')
	{
		dst[f + i] = src[i];
		i++;
	}
	dst[f + i] = '\0';
	return (f + c);
}
