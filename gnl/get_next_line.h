/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mougnou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 22:07:21 by mougnou           #+#    #+#             */
/*   Updated: 2019/11/14 22:08:38 by mougnou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1024

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include "../libft/libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ftt_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *dst, char *src);
char	*ft_strdup(const char *s1);
// size_t	ft_strlen(const char *str);
int		get_next_line(int fd, char **line);
#endif
