#include "minishell.h"

char    *read_line()
{
	char    *cmd;
	char	buf[1024];
	int 	cmdlen;


cmd = malloc(2048 * sizeof(char));
cmdlen = read(0,&buf,2048); //leaks
while (cmdlen != 0)
{
	if (cmdlen == -1)
	{
		printf("Error: %s\n",strerror(errno));
		exit(1);
	}
	strcpy(cmd, buf);
	if (cmd == NULL)
	{
		printf("Error: %s\n",strerror(errno));
		exit(1);
	}
	if (cmd[cmdlen - 1] == '\n')
	{
			cmd[cmdlen] = '\0';
			return cmd;
	}
	cmdlen = read(0,&buf,2048);
}
	 return (0);
}