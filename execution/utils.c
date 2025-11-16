/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:24:12 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/16 17:51:52 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
int is_builtin(char *cmd)
{
        if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "exit")
                || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
                return (1);
        return (0);
}

void	print_envs(t_envp *list)
{
	t_envp	*node;

	node = list;
	while (node)
	{
		printf("%s=", node->key);
		if (node->value)
			printf("%s", node->value);
		printf("\n");
		node = node->next;
	}
}