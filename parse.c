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

	if (src->foundred == 0)
	{
		head->cmd = find_command(pipe[src->c], src->offset, src, envp);
		count = count_argument(pipe[src->c],src->offset,src);
		src->count = count;
		src->dquotes = 0;
		src->squotes = 0;
		head->arg = malloc((count + 1) * sizeof(char *));
		while (i < count)
		{
			head->arg[i] = find_argument(pipe[src->c], src->offset, src, envp);
			i++;
		}
		head->arg[i] = NULL;
	}
	// else 
	// {
	// 	count = 0;
	// 	head->cmd = find_command(src->redsplit[0], src->offset, src, envp);
	// 	i = 0;
	// 	while (src->redsplit[i] != NULL)
	// 	{
	// 		count = count + count_argument(src->redsplit[i], src->offset, src);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	head->arg = malloc((count + 1) * sizeof(char *));
	// 	// head->arg[i++] = find_argument(src->redsplit[0], src->offset, src, envp);
	// 	// printf("%s\n",head->arg[0]);
	// 	c = 0;
	// 	printf("%d\n",count);
	// 	while(src->redsplit[c] != NULL)
	// 	{
	// 		head->arg[i] = find_argument(src->redsplit[c], find_space(src, c), src, envp);
	// 		printf("%s\n",head->arg[i]);
	// 		i++;
	// 		c++;
	// 	}
	// }
	i = 0;
	// printf("Found Red: %d, N: %d\n",src->foundred,src->nred);
	// while (head->arg[i] != NULL)
	// {
	// 	printf("arg %d : %s\n", i, head->arg[i]);
	// 	i++;
	// }
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