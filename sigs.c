#include "minishell.h"

void	handler(int c)
{
	write(1, "\n", 1);
	print_prompt1();
	g_global.fsignal = 1;
	g_global.return_value = 1;
	if (g_global.ffork != 1 && g_global.ret != NULL )
	{
		free(g_global.ret);
		g_global.ret = NULL;
	}
	c++;
}

void	handler2(int c)
{
	if ((g_global.ret && ft_strlen(g_global.ret) > 0) || g_global.ffork == 1)
	{
		write(2, "Quit: ", 6);
		fprintf(stderr, "%d", c);
		write(2, "\n", 1);
		if (g_global.ffork != 1)
			exit(120);
	}
	c++;
}

void	sigs(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler2);
	if (g_global.fsignal == 0)
	{
		print_prompt1();
		g_global.fsignal = 1;
	}
	g_global.ret = NULL;
}
