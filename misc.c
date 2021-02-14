#include "minishell.h"

void clear()
{
    system("clear");
}

void    print_prompt1()
{
		write(1,"Maro-$ ",sizeof("Maro-$ "));
}


void    print_prompt2()
{
		write(1,"> ",sizeof("> "));
}