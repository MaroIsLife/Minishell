/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:23:18 by mougnou           #+#    #+#             */
/*   Updated: 2019/10/31 16:19:48 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int					i;
	char				*p;
	int					a;

	if (s == 0)
		return (0);
	i = 0;
	a = ft_strlen((char *)s);
	p = malloc(a + 1 * sizeof(char));
	if (p == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
	return (0);
}
