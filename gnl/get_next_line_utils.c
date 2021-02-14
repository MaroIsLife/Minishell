/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:50:12 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/14 22:07:07 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char		*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*s1;
	size_t		size;
	size_t		c;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	i = 0;
	size = len + 1;
	s1 = malloc(size * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	c = start;
	while (s[c] != '\0' && i < len)
	{
		s1[i] = s[c];
		i++;
		c++;
	}
	s1[i] = '\0';
	return (s1);
}

char		*ft_strjoin(char *dst, char *src)
{
	char	*p;
	int		size;
	int		b;
	int		i;

	if (dst == 0 || src == 0)
		return (0);
	i = -1;
	size = ft_strlen((char *)dst) + ft_strlen((char *)src) + 1;
	if (!(p = malloc(size * sizeof(char))))
		return (NULL);
	while (dst[++i] != '\0')
		p[i] = dst[i];
	b = 0;
	while (src[b] != '\0')
	{
		p[i] = src[b];
		i++;
		b++;
	}
	p[i] = '\0';
	// free(dst);
	// free(src);
	return (p);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*p;
	int		size;

	i = 0;
	size = ft_strlen(s1) + 1;
	p = malloc(size * sizeof(char));
	if (p == 0)
		return (NULL);
	while (i < size)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

char		*ftt_substr(char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*s1;
	size_t		size;
	size_t		c;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	i = 0;
	size = len + 1;
	s1 = malloc(size * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	c = start;
	while (s[c] != '\0' && i < len)
	{
		s1[i] = s[c];
		i++;
		c++;
	}
	s1[i] = '\0';
	free(s);
	return (s1);
}
