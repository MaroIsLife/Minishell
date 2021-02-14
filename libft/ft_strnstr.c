/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:21:53 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 22:28:52 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	if (ft_strlen(n) == 0)
		return ((char *)h);
	if (len == 0)
		return (0);
	while (h[i] && i < len)
	{
		j = 0;
		k = i;
		while (h[i + j] == n[j] && i + j < len)
		{
			j++;
			if (n[j] == '\0')
				return ((char *)&h[k]);
		}
		i++;
	}
	return (0);
}
