#include "minishell.h"

char	*ft_strjoinchar(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (s == NULL)
	{
		str = malloc(2);
		str[0] = c;
		str[1] = 0;
		return (str);
	}
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

int	get_char(void)
{
	char			c;
	int				total;
	struct termios	term;
	struct termios	init;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	while (read(0, &c, 1) <= 0)
		;
	total += c;
	while (read(0, &c, 1) > 0)
		total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);
}

int	ft_putc(int s)
{
	return (write(1, &s, 1));
}

void	ft_key_remove(t_var *var)
{
	int	i;

	i = 0;
	if (strlen(g_global.ret) > 0)
	{
		while (i < (strlen(g_global.ret) - 1))
			i++;
		tputs(tgetstr("le", NULL), 1, ft_putc);
		tputs(tgetstr("dc", NULL), 1, ft_putc);
		if (!var->edit)
			;
		g_global.ret[i] = '\0';
	}
}

void	ft_key_down(t_stack **tmp, t_var *var)
{
	char	*tmp2;

	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putc);
	tputs(tgetstr("dl", NULL), 1, ft_putc);
	print_prompt1();
	if (*tmp && (*tmp)->prev)
	{
		*tmp = (*tmp)->prev;
		tmp2 = g_global.ret;
		g_global.ret = ft_strdup((char *)(*tmp)->data);
		free(tmp2);
		write(1, (*tmp)->data, strlen((*tmp)->data));
	}
	else
	{
		tmp2 = g_global.ret;
		g_global.ret = ft_strdup("");
		var->help = 0;
		free(tmp2);
		write(1, g_global.ret, strlen(g_global.ret));
	}
	var->edit = 0;
}
