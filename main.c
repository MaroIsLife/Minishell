
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

void	push(char *cmd, char *arg, int num) 
{
	
	t_node		*tmp;

	tmp = g_head;
    while (g_head->next != NULL) {
        g_head = g_head->next;
    }

    g_head->next = (t_node *) malloc(sizeof(t_node));
    g_head->next->number = num;
	g_head->next->arg = arg;
    g_head->next->cmd = cmd;
    // g_head->next->pipe = num;
    g_head->next->next = NULL;
	g_head = tmp;
}


void	ms_loop()
{
	char *cmd;
	char **token;
	char *command;
	char *argument;
	int i = 0;

	while(1)
	{
		print_prompt1();
		cmd = read_line();
		char **argss;
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

		

		// push(12);
		// push(31);

		// token = splits(cmd);
		find_for_split(cmd);
		// if (g_find.foundSemiColons == 1)
		// {
		// 	token = ft_split(cmd,';');
		// }
		// // else 
		// {
		// 	token = NULL;
		// }
		if (g_find.foundPipe == 1)
		{
			i = 0;
			while (cmd[i] != '\0')
			{
					finding_quotes(cmd,i);
				if (cmd[i] == '|' && g_dQuotes == 0)
				{
					i++;
					while (cmd[i] == ' ')
					{
						i++;
					}
					int start = i;
					while (cmd[i] != ' ')
					{
						i++;
					}
					command = ft_substr(cmd,start,i - start);
					printf("%s\n",command);
				}

					i++;
			}

			printf("Found Pipe\n");
		}
		// command = find_command(cmd);
		// argument = find_argument(cmd);
		// printf("%s\n",token[0]);
		i = 0;
		// while (token[i] != NULL)
		// {
			command = find_command(cmd);
			argument = find_argument(cmd);


			printf("#%d Command: %s Argument: %s\n",i,command,argument);
			g_source.offset = 0;
		// 	i++;
		// }
		
		// int i = 0;
		// while (token[i] != NULL)
		// {
		// 	printf("%s\n",token[i]);
		// 	i++;
		// }



		free(command);
		free(cmd);
		free(argument);
		free(token);
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
