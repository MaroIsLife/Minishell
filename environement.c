#include "minishell.h"

int		ft_isdollar(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
	{
		return (1);
	}
	return (0);
}
