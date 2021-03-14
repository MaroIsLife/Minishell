#include "minishell.h"


void    print_prompt1()
{
		write(1,"\033[0;32mMaro-&-Ma3toub$ \033[0;39m",sizeof("\033[0;32mMaro-&-Ma3toub$ \033[0;39m"));
}