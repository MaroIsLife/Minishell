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

void init_arg(t_node *head, char **arg)
{
	int b;
	int i;

	i = 0;
	b = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] != '\0')
			b++;
		i++;
	}
	head->arg = malloc((b + 1) * sizeof(char *));
	i = 0;
	b = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] != '\0')
			head->arg[b++] = arg[i];
		i++;
	}
	head->arg[b] = NULL;
}

void init_arg_pipe(char **arg, t_pipe *p)
{
	int b;
	int i;

	i = 0;
	b = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] != '\0')
			b++;
		i++;
	}
	p->arg = malloc((b + 1) * sizeof(char *));
	i = 0;
	b = 0;
	while (arg[i] != NULL)
	{
		if (arg[i][0] != '\0')
			p->arg[b++] = arg[i];

		i++;
	}
	p->arg[b] = NULL;
}

void loop_pipe(t_source *src, char **envp, t_node *head, char **pipe)
{
	int c;
	int count;
	char **arg;
	t_pipe *p;
	int i;

	c = 0;
	i = 0;
	p = head->pipe;
	while (c < src->npipe)
	{
		src->offset = src->offset + 2; //Whie pipe[c][offset] == '|' offset ++    try putting two pipes near eachother
		p->cmd = find_command(pipe[src->c], head, src, envp);
		count = count_argument(pipe[src->c], src->offset, src);
		i = 0;
		arg = malloc((count + 1) * sizeof(char *));
		while (i < count)
		{
			arg[i] = find_argument(pipe[src->c], head, src, envp);
			i++;
		}
		arg[i] = NULL;
		init_arg_pipe(arg, p);
		p->next = (t_pipe *)malloc(sizeof(t_pipe));
		p->next->next = NULL;
		p = p->next;
		c++;
	}
}

void init_parse(t_source *src, t_node *head, char **envp, char **pipe)
{
	int i = 0;
	int c = 0;
	int count;
	char **arg;
	t_pipe *p;

	src->dollarused = 0;
	head->cmd = find_command(pipe[src->c], head, src, envp);
	// printf("Cmd: %s\n",head->cmd);
	count = count_argument(pipe[src->c], src->offset, src);
	// printf("Count: %d\n",count);
	src->count = count;
	src->dquotes = 0;
	src->squotes = 0;
	arg = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		arg[i] = find_argument(pipe[src->c], head, src, envp);
		i++;
	}
	arg[i] = NULL;
	init_arg(head, arg);
	i = 0;
	// while (head->arg[i] != NULL)
	// {
	// 	printf("%d Arg: |%s|\n",i, head->arg[i]);
	// 	i++;
	// }
	i = 0;
	p = head->pipe;
	if (src->foundpipe == 1)
	{
		loop_pipe(src, envp, head, pipe);
	}
}