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
			// puts ("FOUND");
			char *s;
			s = malloc(100);
			s = getcwd(s,100);
			// puts("CURRENT");
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
void set_old_env(t_source *src, char * pwd)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (src->our_envp[i] != NULL)
	{
		if (ft_strncmp(src->our_envp[i],"OLDPWD", 6) == 0)
		{
			check = 1;
			free(src->our_envp[i]);
			src->our_envp[i] = ft_strjoin("OLD", pwd);
			set_old_env(src, src->our_envp[i]);
			break ;
		}
		i++;
	}
	if(!check)
		{
			src->our_envp[src->lastenv - 1] = ft_strdup(pwd);
			// src->our_envp[src->lastenv] = NULL;
		}
}
void set_old_pwd(t_source *src , char *pwd)
{
	int i;

	i = 0;
	while (src->export[i] != NULL)
	{
		if (ft_strncmp(src->export[i],"OLDPWD", 6) == 0)
		{
			
			free(src->export[i]);
			src->export[i] = ft_strjoin("OLD", pwd);
			set_old_env(src, src->export[i]);
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
			
			set_old_pwd(src, src->export[i]);
			free(src->export[i]);
			src->export[i] =  NULL;
			src->export[i] = ft_strjoin( "PWD=",s );
			free(s);
			break ;
		}
		i++;
	}
}