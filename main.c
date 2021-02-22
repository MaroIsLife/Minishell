
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"


void clearScreen()
{
  char *CLEAR_SCREEN_ANSI;
  CLEAR_SCREEN_ANSI = malloc(1024 * sizeof(char));
  CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(1, CLEAR_SCREEN_ANSI, 12);
  free(CLEAR_SCREEN_ANSI);
}


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

void	push(char *cmd, char *arg, int num) 
{
	t_node		*tmp;
	
	tmp = g_head;
    while (g_head->next != NULL) {
        g_head = g_head->next;
    }

    g_head->next = (t_node *) malloc(sizeof(t_node));
    g_head->next->number = num;
	// g_head->next->arg = arg;
    g_head->next->cmd = cmd;
    // g_head->next->pipe = num;
    g_head->next->next = NULL;
	g_head = tmp;
}

int count_argument(char *s, int offset) //CONVERT TO SPLIT?
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && i == 0)
			g_dquotes = 1;
		else if (s[i] == '\'' && i == 0)
			g_squotes = 1;
		else
			finding_quotes(s, i);
		if ((s[i] == ';' || s[i] == '|') && (g_dquotes == 0 && g_squotes == 0))
			return (count);
		if (s[i] == ' ' && g_dquotes == 0 && g_squotes == 0)
		{
			while (s[i] == ' ')
				i++;
			if ((s[i] == '|' || s[i] == ';') && g_dquotes == 0 && g_squotes == 0)
				return (count);
			count++;
		}
		else
			i++;
	}
	return(count);
}
void init()
{
	g_find.founderror = 0;
	g_find.foundPipe = 0;
	g_source.offset = 0;
	g_source.cmdlen = 0;
	g_source.isPipe = 0;
	g_dquotes = 0;
	g_dquotes = 0;
	g_aSlash = 0;
}


void	ms_loop()
{
	char *cmd;
	int count;
	int i = 0;

	while(1)
	{
		print_prompt1();
		cmd = read_line();
		if (ft_strncmp(cmd,"print",5) == 0)
			printf("Hello\n");

		if (ft_strncmp(cmd,"exit",4) == 0)
			exit(0);
		if (ft_strncmp(cmd,"clear",5) == 0)
			system("clear");

		// if (ft_strncmp(command,"cat",3) == 0)
		// {
		// 	execve("/bin/cat","path.txt",)
		// }

		init();

		// push(12);
		// push(31);
		g_head = (t_node *) malloc(sizeof(t_node));
		g_head->next = NULL;
		g_head->pipe = (t_pipe *) malloc(sizeof(t_pipe));
		g_head->pipe->next = NULL;
		g_first = g_head;

		// find_for_split(cmd);
		g_head->cmd = find_command(cmd, g_source.offset);
		count = count_argument(cmd,0);
		printf("S: %d\n",g_dquotes);
		printf("Found Error: %d\n",g_find.founderror);
		printf("Command: %s\n",g_head->cmd);
		// printf("Argument's Offset: %d\n",g_source.offset);
		i = 0;
		printf("count: %d\n",count);
		g_head->arg = malloc((count + 1) * sizeof(char *));
		// printf("%s\n",find_argument(cmd,g_source.offset));
		while (i < count)
		{
			g_head->arg[i] = find_argument(cmd, g_source.offset);
			i++;
		}
		g_head->arg[i] = NULL;
		i = 0;
		while (g_head->arg[i] != NULL)
		{
			printf("Argument %d : %s\n",i,g_head->arg[i]);
			i++;
		}

		//FIX "echo" "hello" !!!
		//echo "\hello\\\""
		//echo "hello\\
		//echo "hello\\"  FIX THIS
	//echo ' "ab" '

	
		// if (g_find.foundPipe == 1)
		// {
		// 	i = 0;
		// 	while (cmd[i] != '\0')
		// 	{
		// 			finding_quotes(cmd,i);
		// 		if (cmd[i] == '|' && g_dquotes == 0)
		// 		{
		// 			i++;
		// 			while (cmd[i] == ' ')
		// 			{
		// 				i++;
		// 			}
		// 			int start = i;
		// 			while (cmd[i] != ' ')
		// 			{
		// 				i++;
		// 			}
		// 			command = ft_substr(cmd,start,i - start);
		// 		}
		// 			i++;
		// 	}
		// }

		g_source.offset = 0;
		// free(command);
		// free(cmd);
		// free(argument);
		// free(token);
	}
}

int     main()
{

	// clear();
	ms_loop();

	return (0);
}
