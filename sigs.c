#include "minishell.h"

void handler(int c)
{

	if (g_global.fsignal != 0)
		write(1,"\b\b  \b\b",6);
	
	write(1, "\n", 1);
	print_prompt1();
	g_global.fsignal = 1;
	g_global.return_value = 1;

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
