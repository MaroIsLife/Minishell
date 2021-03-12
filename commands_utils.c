# include "minishell.h"

void change_pwd_env(char **envp)
{
	int i = 0;
	int b = 4;
	int c = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i],"PWD",3) == 0)
		{
			char *s;
			s = malloc(100);
			s = getcwd(s,100);
			while (c < ft_strlen(s))
			{
				envp[i][b] = s[c];
				c++;
				b++;
			}
			envp[i][b] = '\0';
			free(s);
			break ;
		}
		i++;
	}
}