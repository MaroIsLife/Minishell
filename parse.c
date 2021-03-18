#include "minishell.h"

int find_space(t_source *src, int i)
{
	int c;

	c = 0;
	while (src->redsplit[i][c] == ' ' && src->redsplit[i][c] != '\0')
		c++;
	while (src->redsplit[i][c] != ' ' && src->redsplit[i][c] != '\0')
		c++;
	return (c);
}

void init_parse(t_source *src, t_node *head, char **envp, char **pipe)
{
	int i = 0;
	int c = 0;
	int count;
	t_pipe *p;

	// if (src->foundred == 0)
	// {
		head->cmd = find_command(pipe[src->c], head, src, envp);
		count = count_argument(pipe[src->c], src->offset, src);
		src->count = count;
		src->dquotes = 0;
		src->squotes = 0;
		head->arg = malloc((count + 1) * sizeof(char *));
		while (i < count)
		{
			head->arg[i] = find_argument(pipe[src->c], head, src, envp);
		if (head->arg[i][0] != '\0')
			i++;
		}
		head->arg[i] = NULL;
	i = 0;
	p = head->pipe;
	if (src->foundpipe == 1)
	{
		c = 0;
		while (c < src->npipe)
		{
			src->offset = src->offset + 2; //Whie pipe[c][offset] == '|' offset ++    try putting two pipes near eachother
			p->cmd = find_command(pipe[src->c], head, src, envp);
			count = count_argument(pipe[src->c], src->offset, src);
			i = 0;
			p->arg = malloc((count + 1) * sizeof(char *));
			while (i < count)
			{
				p->arg[i] = find_argument(pipe[src->c], head, src, envp);
				i++;
			}
			p->arg[i] = NULL;
			// printf("%s\n",p->cmd);
			// i = 0;
			// while (i < count)
			// {
			// 	printf("%s\n",p->arg[i]);
			// 	i++;
			// }
			p->next = (t_pipe *) malloc(sizeof(t_pipe));
			p->next->next = NULL;
			p = p->next;
			c++;
		}
	}
}