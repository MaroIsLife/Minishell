#include "minishell.h"

void	ms_free(t_source *src, t_var *var)
{
	int	n;

	n = 0;
	while (var->pipes[n] != NULL)
	{
		free(var->pipes[n]);
		n++;
	}
	free(var->pipes);
}
