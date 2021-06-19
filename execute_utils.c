#include "minishell.h"

int	calc_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i] != NULL)
		i++;
	return (i);
}

char	**ft_valide_args(char *cmd, char **args, int count)
{
	char	**varg;
	int		i;
	int		b;

	i = 0;
	b = 1;
	varg = malloc (sizeof(char *) * (count + 2));
	varg[0] = ft_strdup(cmd);
	while (args && args[i] != NULL)
		varg[b++] = ft_strdup(args[i++]);
	varg[b] = NULL;
	return (varg);
}

char	**get_env_path(char **envp, t_source *src)
{
	int		i;
	char	*s;
	char	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0 && envp[i][4] == '=')
		{
			s = ft_strchr(envp[i], '=') + 1;
			if (s != 0)
				paths = ft_split_normal(s, ':');
			return (paths);
		}
		i++;
	}
	return (0);
}

char	*get_correct_path(char **s, char **varg)
{
	struct stat		sb;
	char			*tmp;
	char			*tmp2;
	int				i;

	i = 0;
	while (s[i] != NULL)
	{
		tmp = ft_strjoin(s[i], "/");
		tmp2 = ft_strjoin(tmp, varg[0]);
		free(tmp);
		if (stat(tmp2, &sb) != -1)
			return (tmp2);
		else
			free(tmp2);
		i++;
	}
	return (0);
}
