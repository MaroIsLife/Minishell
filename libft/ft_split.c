/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:24:03 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/03 17:45:32 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../gnl/get_next_line.h"
#include "../minishell.h"

int		delimc(char *s, char c, t_source *src)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		while (s[i] != c && s[i] != '\0')
		{
			finding_quotes(s, i, src);
			i++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] == c && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
			n++;
			i++;
	}
	return (n);
}

char		**ft_split(char *s, char c, t_source *src)
{
	int		j;
	int		len;
	int		start;
	int		k;
	char	**p;

	j = delimc(s, c, src) + 2;
	printf("Del: %d\n",j);
	if (!(p = (char **)malloc(j * sizeof(char *))))
		return (NULL);
	k = 0;
	len = 0;
	while (k < j - 1)
	{
		while (s[len] != '\0' && s[len] == c && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
		{
			finding_quotes(s, len, src);
			len++;
		}
		start = len;
		while (s[len] != '\0')
		{
			if (s[len] == c && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
				break ;
			finding_quotes(s, len, src);
			len++;
		}
		p[k++] = ft_substr(s, start, (len - start));
	}
	p[k] = NULL;
	return (p);
}
