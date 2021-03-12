#include "minishell.h"

void    ft_execute (t_node *head, t_source *src, char **envp)
{
    int id;
    id = fork ();
    char **var;
    if (id == 0)
        execve(ft_strjoin("/bin/", head->arg[0]),head->arg, NULL);
    else
        wait(&id);

}

void command_list(t_node *head, t_source *src, char **envp)
{
    if (ft_strncmp(head->cmd, "cd", 2) == 0)
        ft_cd(head, where_home(envp));
    else if (ft_strncmp(head->cmd,"echo",4) == 0)
        ft_echo(head, src);
    else if (ft_strncmp(head->cmd, "env", 3) == 0)
        print_env(head, src, envp);
    else if (ft_strncmp(head->cmd, "export", 6) == 0)
        ft_export(head, src, envp);
    else if (ft_strncmp(head->cmd, "pwd", 3) == 0)
        ft_pwd();
    else if (ft_strncmp(head->cmd, "unset", 5) == 0)
        ft_unset(head, src, envp);
    else
        ft_execute(head, src, envp);
}