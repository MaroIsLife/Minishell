/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:35:22 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 21:51:44 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*dst1;
	const char		*src1;

	i = 0;
	dst1 = (char *)dst;
	src1 = (const char *)src;
	while (i < n)
	{
		if (src1[i] == (char)c)
		{
			dst1[i] = src1[i];
			return (&dst1[i + 1]);
		}
		dst1[i] = src1[i];
		i++;
	}
	return (0);
}
