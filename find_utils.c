#include "minishell.h"

int finding_quotes_cmd(char *s,int i, t_source *src)
{
	if (s[i] == '\"' && i == 0)
		src->dquotes = 1;
	else if (s[i] == '\'' && i == 0 && src->dquotes == 0)
		src->squotes = 1;
	else if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
		{
			if (src->dquotes == 0)
			{
				src->dquotes = 1;
			}
			else
				src->dquotes = 0;
		}
		else if (s[i] == '\'' && src->dquotes == 0)
		{
			if (src->squotes == 0)
				src->squotes = 1;
			else
				src->squotes = 0;
		}
		finding_aslash(s, i, src);
	return 0;
}

int finding_quotes(char *s,int i, t_source *src)
{
	if (s[i] == '\"' && src->squotes == 0 && src->aslash == 0)
	{
			if (src->dquotes == 0)
			{
				src->dquotes = 1;
			}
			else
				src->dquotes = 0;
	}
	else if (s[i] == '\'' && src->dquotes == 0 && src->aslash == 0)
	{
			if (src->squotes == 0)
			{
				src->squotes = 1;
			}
			else
				src->squotes = 0;
	}
	finding_aslash(s, i, src);
	return 0;
}

int		finding_aslash(char *s, int i, t_source *src)
{
		if (s[i] == '\\' && s[i + 1] == '\'' && src->dquotes == 1)
			src->aslash = 0;
		else if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\\' || s[i + 1] == '\'' || s[i + 1] == '$') && src->aslash == 0 && src->squotes == 0)
		{
			src->aslash = 1;
		}
		else if (s[i] == '\\' && (src->dquotes == 0 && src->squotes == 0))
		{
			if (ft_isascii(s[i + 1]) == 0)
				src->founderror = 1;
			else
				return (1);
		}
		else
			src->aslash = 0; //convert to return 0 or 1 for norminette?
	return 0;
}

void	find_for_split(char *cmd, t_source *src)
{
	int i;
	char **token;

	i = 0;
	src->foundpipe = 0;
	src->npipe = 0;
	src->dquotes = 0;
	src->squotes = 0;

	while (cmd[i] != '\0')
	{
		finding_quotes_cmd(cmd,i, src);
		if (cmd[i] == '|' && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
		{
			src->foundpipe = 1;
			src->npipe++;
		}
		// else if (cmd[i] == '>' && src->dquotes == 0 && src->squotes == 0 && src->aslash == 0)
		// {
		// 	src->foundpipe = 1;
		// 	src->npipe++;
		// }
		i++;
	}
	if (src->dquotes == 1 || src->squotes == 1 || src->aslash == 1)
		src->founderror = 1;
	// printf("%d\n",g_find.ndquotes); //Bugged to fix later
}

int		find_equal_length(char **envp,int c, int b)
{
	int length;

	length = 0;

	while (envp[c][b] != '=' && envp[c][b] != '\0')
	{
		b++;
		length++;
	}
	
	return length; 
}


int		get_env_value_arg(char *s, char **envp, t_source *src, int i)
{
	char	*temp;
	int		b;
	int		c;

	i = i + 1;
	b = 0;
	c = 0;
	temp = malloc(1024 * sizeof(char));
	while (s[i] != '$' && s[i] != '\n' && s[i] != '\0' && s[i] != ' ')
	{
		temp[b++] = s[i++];
		if (ft_isalpha(s[i]) != 1)
			break ;
	}
	temp[b] = '\0';
	b = 0;
	while (envp[c] != NULL)
	{
		if (ft_strncmp(envp[c], temp, find_equal_length(envp, c, b)) == 0)
		{
			while (envp[c][b] != '=' && envp[c][b] != '\0')
				b++;
				while (envp[c][++b] != '\0')
					src->re[src->re_b++] = envp[c][b];
				break ;
		}
		c++;
	}
	free(temp);
	return (i);
}



