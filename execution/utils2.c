/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 01:54:20 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/06 01:54:40 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_execve_error(char *path, char **envp, t_data *data,
		t_envp *env)
{
	perror(path);
	free(path);
	ft_free2d(envp);
	exit_with_cleanup(data, env, 126);
}

char	*search_path(char **dirs, char *cmd)
{
	char	*res;
	int		i;

	i = 0;
	while (dirs[i])
	{
		res = path_check(dirs[i], cmd);
		if (res)
			return (res);
		i++;
	}
	return (NULL);
}

char	*cmd_path(char *cmd, char **envp)
{
	char	**dirs;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	dirs = get_path(envp);
	if (!dirs)
		return (NULL);
	res = search_path(dirs, cmd);
	ft_free2d(dirs);
	return (res);
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	is_child_builtin(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}
