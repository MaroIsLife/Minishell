#include "minishell.h"


void    print_prompt1()
{
		write(1,"\033[0;32mMinishell$ \033[0;39m",sizeof("\033[0;32mMinishell$ \033[0;39m"));
}