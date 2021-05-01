# include "minishell.h"

void change_pwd_env(t_source *src)
{
	int i = 0;
	int b = 4;
	int c = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(src->our_envp[i],"PWD",3) == 0)
		{
			char *s;
			s = malloc(100);
			s = getcwd(s,100);
			puts("CURRENT");
			puts (s);
			while (c < ft_strlen(s))
			{
				src->our_envp[i][b] = s[c];
				c++;
				b++;
			}
			src->our_envp[i][b] = '\0';
			free(s);
			break ;
		}
		i++;
	}
}
void change_pwd_export(t_source *src)
{
	int i = 0;
	int b = 4;
	int c = 0;
	while (src->export[i] != NULL)
	{
		if (ft_strncmp(src->export[i],"PWD",3) == 0)
		{
			char *s;
			s = malloc(100);
			s = getcwd(s,100);
			puts("CURRENT");
			puts (s);
			while (c < ft_strlen(s))
			{
				src->export[i][b] = s[c];
				c++;
				b++;
			}
			src->export[i][b] = '\0';
			free(s);
			break ;
		}
		i++;
	}
}