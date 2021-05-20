#include "minishell.h"

char    *read_line()
{
	char    *cmd;
	char	buf[1024];
	int 	cmdlen;


cmd = malloc(1024 * sizeof(char));
cmdlen = read(0,&buf,1024); //leaks
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
	cmdlen = read(0,&buf,1024);
}
	 return (0);
}