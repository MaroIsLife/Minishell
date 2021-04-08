// #include "minishell.h"
// #include <termcap.h>

// char    *read_line()
// {
// 	char    *cmd;
// 	char	buf[1024];
// 	int 	cmdlen;


// cmd = malloc(1024 * sizeof(char));
// cmdlen = read(0,&buf,1024); //leaks
// while (cmdlen != 0)
// {
// 	if (cmdlen == -1)
// 	{
// 		printf("Error: %s\n",strerror(errno));
// 		exit(1);
// 	}
// 	strcpy(cmd, buf);
// 	if (cmd == NULL)
// 	{
// 		printf("Error: %s\n",strerror(errno));
// 		exit(1);
// 	}
// 	if (cmd[cmdlen - 1] == '\n')
// 	{
// 			cmd[cmdlen] = '\0';
// 			return cmd;
// 	}
// 	cmdlen = read(0,&buf,1024);
// }
// 	 return (0);
// }

// void    print_prompt1()
// {
// 		write(1,"\033[0;32mTermCap$ \033[0;39m",sizeof("\033[0;32mTermCap$ \033[0;39m"));
// }

// int main()
// {
//     char *s;

//     print_prompt1();

//     while(1)
//     {
//         s = read_line();
//         if (s == NULL)
//             exit(0);
//         printf("%s",s);
//         print_prompt1();


//     }

//     return (0);
// }