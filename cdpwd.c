#include "minishell.h"

char	*where_home(t_source *src)
{
	int		i;
	char	*home;

	i = 0;
	while (src->our_envp[i])
	{
		if (ft_strncmp(src->our_envp[i], "HOME=", 5) == 0)
		{
			home = malloc (ft_strlen(src->our_envp[i] + 5) + 1);
			ft_strlcpy(home, src->our_envp[i] + 5,
				ft_strlen(src->our_envp[i] + 5) + 1);
			return (home);
		}
		i++;
	}
	return (0);
}

void	ft_pwd (void)
{
	char	*s;

	s = malloc(100 * sizeof(char));
	printf("%s\n", getcwd(s, 100));
	free (s);
}

void	ft_cd(char **args, t_source *src, char *home)
{
	int	sign;

	sign = 0;
	if (!args[0])
	{
		if (!home)
			write(1, "minishell: cd: HOME not set\n", 23);
		else
			chdir(home);
	}
	else
		sign = chdir(args[0]);
	if (sign != 0)
		printf ("Error: %s\n", strerror(errno));
	change_pwd_env(src);
	change_pwd_export(src);
}
