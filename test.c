#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
void    print_prompt1()
{
		write(1,"\033[0;32m3ayn_chou9$ \033[0;39m",sizeof("\033[0;32m3ayn_chou9$ \033[0;39m"));
}

int main() {
  


    while (1)
    {
        char *l = malloc (1024);
        print_prompt1();
        l  = read_line();
        puts(l);
       }
    return 0;
}