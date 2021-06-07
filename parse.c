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

t_filename		*new_file(char *s, t_source *src)
{
	t_filename *tmp;

		tmp = (t_filename *) malloc(sizeof(t_filename));
		tmp->next = NULL;
		tmp->filename = ft_strdup(s);
		tmp->c = src->p->c;
		return (tmp);
}

t_filename *get_last_node(t_filename *tmp)
{
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void init_file(t_source *src)
{
	t_filename	*tmp;
	if (src->npipe > 0 && src->foundred == 1)
	{

		tmp = get_last_node(src->ptemp->pipef);
		if (tmp == NULL)
				src->ptemp->pipef = new_file(src->p->filename, src);
		else
			tmp->next = new_file(src->p->filename, src);
	}
}

t_pipe	*new_pipe(char **pipe, t_source *src, t_node *head)
{
	t_pipe *tmp;
	char **arg;
	int count;
	int i;

		tmp = (t_pipe *) malloc(sizeof(t_pipe));
		tmp->next = NULL;
		// tmp->pipef = (t_filename *)malloc(sizeof(t_filename));
		// tmp->pipef->next = NULL;
		tmp->pipef = NULL;
		src->ptemp = tmp;
		tmp->cmd = find_command(pipe[src->c], head, src, src->our_envp);
		count = count_argument(pipe[src->c], src->offset, src);
		i = 0;
		arg = malloc((count + 1) * sizeof(char *));
		while (i < count)
		{
			arg[i] = find_argument(pipe[src->c], head, src, src->our_envp);
			// printf("Fname: %s\n",src->p->filename);
			// init_file(src);
			i++;
		}
		arg[i] = NULL;
		init_arg_pipe(arg, tmp);
	return (tmp);
}

void loop_pipe(t_source *src, char **envp, t_node *head, char **pipe)
{
	int c;
	int count;
	// char **arg;
	t_pipe	*tmp;
	int i;

	c = 0;
	i = 0;
	while (c < src->npipe)
	{
		// printf("Here\n");
		src->offset = src->offset; //Whie pipe[c][offset] == '|' offset ++    try putting two pipes near eachother
		// src->ptemp = head->pipe;
		if (head->pipe == NULL)
		{
						// printf("One\n");
			head->pipe = new_pipe(pipe, src, head);
			tmp = head->pipe;
		}
		else
		{
			// printf("Two\n");
			tmp->next = new_pipe(pipe, src, head); 
			// while (1)
			// {
			// 		if (!tmp || tmp->next == NULL)
			// 			break ;
			// 	tmp = tmp->next;
			// }
			// tmp = new_pipe(pipe, src, head);
		}
		// printf("file: %s\n",tmp->pipef->filename);
		c++;
	}

	// tmp->next = NULL;
	// if (head->pipe == NULL)-
	// 	printf("NULL\n");
	// tmp = head->pipe;
	// while (1)
	// {
	// 	// printf("Filename: %s\n",tmp->pipef->filename);
	// 	// printf("Here\n");
	// 	int po = 0;
	// 	// while (head->pipe->arg[po] != NULL)
	// 	// 	printf("Arg: %s\n",head->pipe->arg[po++]);
	// 	if (tmp->next == NULL)
	// 		break ;
	// 	tmp = tmp->next;
	// }
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
	// free(src->ra);
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