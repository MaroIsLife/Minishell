/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 21:48:54 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/14 22:02:16 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_counter(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

int		ft_free(char *s, char *str, int i)
{
	free(s);
	free(str);
	return (i);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	char		*s;
	static char	*str;

	*line = ft_strdup("");
	while (1)
	{
		s = str;
		if (str == NULL)
		{
			s = malloc(BUFFER_SIZE + 1 * sizeof(char));
			if ((!(i = read(fd, s, BUFFER_SIZE))) || i == -1)
				return (ft_free(s, str, i));
			s[i] = 0;
		}
		i = ft_counter(s);
		if (s[i] == '\n')
		{
			*line = ft_strjoin(*line, ft_substr(s, 0, i));
			str = ftt_substr(s, i + 1, ft_strlen(s) - i + 1);
			return (1);
		}
		*line = ft_strjoin(*line, s);
		str = NULL;
	}
}
