# include "minishell.h"

void change_pwd_env(t_source *src)
{
	int i = 0;
	int b = 4;
	int c = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(src->our_envp[i],"PWD=", 4) == 0)
		{
			puts ("FOUND");
			char *s;
			s = malloc(100);
			s = getcwd(s,100);
			puts("CURRENT");
			puts (s);
			free(src->our_envp[i]);
			src->our_envp[i] =  NULL;
			// while (c < ft_strlen(s))
			// {
			src->our_envp[i] = ft_strjoin( "PWD =",s );
			// 	c++;
			// 	b++;
			// }
			// src->our_envp[i][b] = '\0';
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
		if (ft_strncmp(src->export[i],"PWD=", 4) == 0)
		{
			puts ("FOUND");
			char *s;
			s = malloc(100);
			s = getcwd(s,100);
			puts("CURRENT");
			puts (s);
			free(src->export[i]);
			src->export[i] =  NULL;
			src->export[i] = ft_strjoin( "PWD=",s );
			free(s);
			break ;
		}
		i++;
	}
}