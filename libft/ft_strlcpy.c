/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:11:03 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 22:30:42 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	char			*src1;
	size_t			i;
	size_t			c;
	size_t			len;

	i = 0;
	len = size - 1;
	src1 = (char *)src;
	c = ft_strlen(src1);
	if (size == 0)
		return (c);
	while (i < c && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (c);
}
