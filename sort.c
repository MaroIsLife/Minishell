#include "minishell.h"

void	ft_sort_two(t_source *src, int *i, int *j, int *n)
{
	if (src->export[(*i)][0] > src->export[(*j)][0])
	{
		src->ctmp2 = src->export[(*i)];
		src->export[(*i)] = src->export[(*j)];
		src->export[(*j)] = src->ctmp2;
	}
	if (src->export[(*i)][0] == src->export[(*j)][0])
	{
		(*n) = 1;
		while (src->export[(*j)][(*n)] != '\0' && src->export[(*i)][(*n)] != '\0')
		{
			if (src->export[(*i)][(*n)] > src->export[(*j)][(*n)])
			{
				src->ctmp2 = src->export[(*i)];
				src->export[(*i)] = src->export[(*j)];
				src->export[(*j)] = src->ctmp2;
			}
			(*n)++;
		}
	}
	(*j)++;
}

void 	ft_sort(t_source *src)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (i < src->lastexp && src->export[i] != NULL)
	{
		j = i + 1;
		while ((j) < src->lastexp && src->export[(j)] != NULL)
			ft_sort_two(src, &i, &j, &n);
		i++;
	}
}
