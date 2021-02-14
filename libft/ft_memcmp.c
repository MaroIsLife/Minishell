/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:16:25 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 20:11:07 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_memcmp(const void *s1, const void *s2, size_t length)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	while (i < length)
	{
		if (ss1[i] == ss2[i])
		{
			i++;
		}
		else
		{
			return (ss1[i] - ss2[i]);
		}
	}
	return (0);
}
