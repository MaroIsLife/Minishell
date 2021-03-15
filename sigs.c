#include "minishell.h"

void handler(int c)
{

	if (g_id != 0)
	{
		write(1,"\b\b  \b\b",6);
		write(1,"\r\n",2);
		print_prompt1();
	}

	// write(1,"\b\b  \b\b",6);
	// write(1,"\n",1);
	// print_prompt1();

	//return 1
}

void handler2(int c)
{
	write(1,"Quit: ",5);
	write(2,"\n",1);
	exit (0);
}
