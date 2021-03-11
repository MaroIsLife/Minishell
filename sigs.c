#include "minishell.h"

void handler(int c)
{

	write(2,"\b\b  \b\b",5);
	write(2,"\n",1);
	print_prompt1();
	//return 1

}

void handler2(int c)
{

	write(1,"Quit: ",5);
	write(2,"\n",1);
	exit (0);

}
