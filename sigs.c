#include "minishell.h"

void handler(int c)
{

	// if (g_global.fsignal != 0)
	// 	write(1,"\b\b  \b\b",6);
	
	write(1, "\n", 1);
	print_prompt1();
	g_global.fsignal = 1;
	g_global.return_value = 1;

	if (g_global.ret != NULL)
	{
		// free(g_global.ret);
		g_global.ret = NULL;
	}

	// write(1,"\b\b  \b\b",6);
	// write(1,"\n",1);
	// print_prompt1();

	//return 1
}

void handler2(int c)
{
	// write(1,"\b\b  \b\b",sizeof("\b\b  \b\b"));
	write(2,"Quit: ",6);
	fprintf(stderr, "%d", c);
	write(2,"\n",1);
	print_prompt1();
	g_global.fsignal = 1;
}
