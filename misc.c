#include "minishell.h"

void clear()
{
    system("clear");
}

void    print_prompt1()
{
		write(1,"\033[0;32mMaro-$ \033[0;39m",sizeof("\033[0;32mMaro-$ \033[0;39m"));
}