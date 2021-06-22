#	include "minishell.h"

void	change_pwd_env(t_source *src)
{
	int		i;
	int		b;
	char	*s;
	int		c;

	c = 0;
	b = 4;
	i = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(src->our_envp[i], "PWD=", 4) == 0)
		{
			s = malloc(100);
			s = getcwd(s, 100);
			free(src->our_envp[i]);
			src->our_envp[i] = NULL;
			src->our_envp[i] = ft_strjoin("PWD=", s);
			free(s);
			break ;
		}
		i++;
	}
}

void	set_old_env(t_source *src, char *pwd)
{
	int	i;
	int	check;
	char *tmp;

	i = 0;
	check = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(src->our_envp[i], "OLDPWD", 6) == 0)
		{
			check = 1;
			tmp = src->our_envp[i];
			src->our_envp[i] = ft_strdup(pwd);
			free(tmp);
			break ;
		}
		i++;
	}
	if (!check)
	{
		src->our_envp[src->lastenv - 1] = ft_strdup(pwd);
	}
}

void	set_old_pwd(t_source *src, char *pwd)
{
	int	i;
	char *tmp;

	i = 0;
	while (src->export[i] != NULL)
	{
		if (ft_strncmp(src->export[i], "OLDPWD", 6) == 0)
		{
			tmp = src->export[i];
			src->export[i] = ft_strjoin("OLD", pwd);
			set_old_env(src, src->export[i]);
			free(tmp);
			break ;
		}
		i++;
	}
}

void	change_pwd_export(t_source *src)
{
	int		i;
	int		b;
	int		c;
	char	*s;

	i = 0;
	b = 4;
	c = 0;
	while (src->export[i] != NULL)
	{
		if (ft_strncmp(src->export[i], "PWD=", 4) == 0)
		{
			s = malloc(100);
			s = getcwd(s, 100);
			set_old_pwd(src, src->export[i]);
			free(src->export[i]);
			src->export[i] = NULL;
			src->export[i] = ft_strjoin("PWD=", s);
			free(s);
			break ;
		}
		i++;
	}
}
