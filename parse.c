#include "minishell.h"

void init_parse(t_source *src, t_node *head, char **envp, char **pipe)
{
	int i = 0;
	int c = 0;
	int count;
	t_pipe *p;

	head->cmd = find_command(pipe[src->c], src->offset, src, envp);
	count = count_argument(pipe[src->c],src->offset,src);
    src->dquotes = 0;
	src->squotes = 0;
	head->arg = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		head->arg[i] = find_argument(pipe[src->c], src->offset, src, envp);
		i++;
	}
	head->arg[i] = NULL;
	i = 0;
	printf ("=======================================\n");
	while (head->arg[i])
		printf("arg %d : %s\n", i, head->arg[i++]);
	printf ("=======================================\n");
	p = head->pipe;
	if (src->foundpipe == 1)
	{
		c = 0;
		while (c < src->npipe)
		{
			src->offset = src->offset + 2;
			p->cmd = find_command(pipe[src->c], src->offset, src, envp);
			count = count_argument(pipe[src->c],src->offset,src);
			i = 0;
			p->arg = malloc((count + 1) * sizeof(char *));
			while (i < count)
			{
				p->arg[i] = find_argument(pipe[src->c], src->offset, src, envp);
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