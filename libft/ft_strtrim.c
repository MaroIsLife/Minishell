/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:25:27 by mougnou           #+#    #+#             */
/*   Updated: 2019/10/31 16:27:30 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		tester(char const s1, const char *set)
{
	int i;
	int k;

	k = ft_strlen((const char *)set);
	i = 0;
	while (i <= k)
	{
		if (s1 != set[i])
		{
			i++;
		}
		else
		{
			return (1);
		}
	}
	return (0);
}

static	int		triml(char const *s1, const char *set)
{
	int i;
	int k;

	i = 0;
	k = ft_strlen(s1);
	while (i <= k)
	{
		if (tester(s1[i], set) == 1)
		{
			i++;
		}
		else
		{
			return (i);
		}
	}
	return (0);
}

static int		trimr(char const *s1, const char *set)
{
	int k;
	int i;

	i = 0;
	k = ft_strlen(s1);
	while (k >= i)
	{
		if (tester(s1[k], set) == 1)
		{
			k--;
		}
		else
		{
			return (k);
		}
	}
	return (ft_strlen((char *)s1));
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	int		c;
	char	*p;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return ((char *)s1);
	k = trimr(s1, set);
	if ((size_t)k != ft_strlen(s1))
		i = triml(s1, set);
	else
		i = k;
	if (!(p = malloc(k - i + 2 * sizeof(char))))
		return (NULL);
	c = 0;
	while (i <= k)
	{
		p[c] = s1[i];
		i++;
		c++;
	}
	p[c] = '\0';
	return (p);
}
