#include "minishell.h"

void	ft_free_filenames(t_filename *head)
{
	t_filename	*here1;
	t_filename	*next1;

	here1 = head;
	while (here1 != NULL)
	{
		next1 = here1->next;
		free(here1->filename);
		free(here1);
		here1 = next1;
	}
}
