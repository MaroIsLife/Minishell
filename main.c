
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"


void	print_list() {
   
   t_node *first;

   first = g_head;
	while(g_head != NULL)
	{
		printf("%d\n",g_head->number);
		g_head = g_head->next;
	}
	g_head = first;
    // while (g_head != NULL) {
    //     printf("%d\n", g_head->number);
    //     g_head = g_head->next;
    // }
}

void	push(char *cmd, char *arg,int num) 
{
	
	t_node		*tmp;

	tmp = g_head;
    while (g_head->next != NULL) {
        g_head = g_head->next;
    }

    g_head->next = (t_node *) malloc(sizeof(t_node));
    g_head->next->number = num;
    g_head->next->next = NULL;
	g_head = tmp;
}


char	**splits(char *cmd)
{
	char **semiColons;
	int i;


	find_for_split(cmd);
	if (g_find.foundSemiColons == 1)
	{
		semiColons = ft_split(cmd,';');
		return semiColons;
	}
	else if (g_find.foundPipe == 1)
	{
		;
	}
	return semiColons;
}

void	find_argument(char *s)
{
	int i;
	int b;
	char *re;
	int dQuotes;
	int sQuotes;

	b = 0;
	dQuotes = 0;
	if (s[i] == '\"')
	{
		;
	}
	i = g_source.offset + 1;
	while (s[i] == ' ')
		i++;
	g_source.offset = i;
	while (s[i] != '\n' && i <= g_source.cmdlen)
	{
		i++;

		if (s[i - 1] != '\\' && s[i] == '\"')
			b--;
		b++; //b = size of Argument
	}
	i = g_source.offset;
	re = malloc((b + 1) * sizeof(char));
	b = 0;
	while (s[i] != '\n' && s[i] != '|' && i <= g_source.cmdlen)
	{
		if (s[i] == ' ')
		{
			re[b] = s[i];
			b++;
			while (s[i + 1] == ' ' && dQuotes == 0)
				i++;
		}
		else if (s[i] == '\"')
		{
			if (dQuotes == 0)
				dQuotes = 1;
			else
				dQuotes = 0;
		}
		else if (s[i] == '\'' && dQuotes == 0)
		{
			if (sQuotes == 0)
				sQuotes = 1;
			else
				sQuotes = 0;
		}
		else
		{
			re[b] = s[i];
			b++;
		}
		i++;
	}
	re[b] = '\0';

	// re = ft_substr(s,(g_source.offset),i - (g_source.offset));
	
	printf("%s\n",re);

}


void	ms_loop()
{
	char *cmd;
	char **token;
	char *command;

	while(1)
	{
		print_prompt1();
		cmd = read_line();

		if (ft_strncmp(cmd,"print",5) == 0)
			printf("Hello\n");

		if (ft_strncmp(cmd,"exit",4) == 0)
			exit(0);

		

		// push(12);
		// push(31);

		token = splits(cmd);
		command = find_command(cmd);
		// int i = 0;
		// while (token[i] != NULL)
		// {
		// 	printf("%s\n",token[i]);
		// 	i++;
		// }
			find_argument(cmd);



		free(command);
		free(cmd);
	}
}

int     main()
{
	g_head = (t_node *) malloc(sizeof(t_node));
	g_head->next = NULL;
	g_first = g_head;

	// clear();
	ms_loop();

	return (0);
}
