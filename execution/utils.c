/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:24:12 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/23 02:10:30 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

// char	*cmd_check(char *argv, char **dir)
// {
// 	int		i;
// 	char	*cmd_path;
// 	char	*path;

// 	i = 0;
// 	while (dir[i])
// 	{
// 		cmd_path = ft_strjoin(dir[i], "/");
// 		path = ft_strjoin(cmd_path, argv);
// 		free(cmd_path);
// 		if (!access(path, F_OK))
// 			return (path);
// 		free(path);
// 		i++;
// 	}
// 	error_exit("wrong command");
// }

int	count_env(t_envp *env)
{
	int	i;
	t_envp	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*res;

	if (!value)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	**list_to_arr(t_envp *env)
{
	char	**envp;
	t_envp	*tmp;
	int	i;

	envp = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		envp[i] = join_key_value(tmp->key, tmp->value);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*path_check(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!path)
		return (NULL);
	if (!access(path, X_OK))
		return (path);
	free(path);
	return (NULL);
}

char	*search_path(char **dirs, char *cmd)
{
	char	*res;
	int	i;

	i = 0;
	while (dirs[i])
	{
		res = path_check(dirs[i], cmd);
		if(res)
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