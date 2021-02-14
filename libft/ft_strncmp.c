/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:05:56 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 22:03:36 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((ss1[i] != '\0' || ss2[i] != '\0') && (ss1[i] == ss2[i]) && (i < n))
	{
		i++;
	}
	if (i == n)
		i--;
	if (ss1[i] != ss2[i])
	{
		return (ss1[i] - ss2[i]);
	}
	return (0);
}
