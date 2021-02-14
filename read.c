#include "minishell.h"

char    *read_line()
{
	char    *cmd;
	char	buf[1024];


cmd = malloc(1024 * sizeof(char));
while ((g_source.cmdlen = read(0,&buf,1024)) != 0)
{
	if (g_source.cmdlen == -1)
	{
		printf("Error: %s\n",strerror(errno));
		exit(1);
	}
	strcpy(cmd,buf);
	if (cmd == NULL)
	{
		printf("Error: %s\n",strerror(errno));
		exit(1);
	}
	if (cmd[g_source.cmdlen - 1] == '\n')
	{
		if (g_source.cmdlen == 1 || cmd[g_source.cmdlen - 2] != '\\')
		{
			cmd[g_source.cmdlen] = '\0';
			return cmd;
		}
		cmd[g_source.cmdlen - 1] = '\0';
		print_prompt2();
	}
}
	 return (0);
}