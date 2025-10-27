#include "../minishell.h"
/*
char    **get_path(char **envp)
{
        int     i;

        i = 0;
        while (envp[i])
        {
                if (!ft_strncmp("PATH=", envp[i], 5))
                        return (ft_split(envp[i] + 5, ':'));
                i++;
        }
        return (NULL);
}

char    *cmd_check(char *argv, char **dir)
{
        int             i;
        char    *cmd_path;
        char    *path;

        i = 0;
        while (dir[i])
        {
                cmd_path = ft_strjoin(dir[i], "/");
                path = ft_strjoin(cmd_path, argv);
                free(cmd_path);
                if (!access(path, F_OK))
                        return (path);
                free(path);
                i++;
        }
        error_exit("wrong command");
}
*/
