/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:58:05 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/30 02:55:40 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_external(t_data *data, t_envp *env)
{
	char	**envp;
	char	*path;

	if (!data->cmd->arg || !data->cmd->arg[0])
		exit(127);
	envp = list_to_arr(env);
	if (!envp)
		exit (1);
	path = cmd_path(data->cmd->arg[0], envp);
	if (!path)
	{
		ft_printf("%s: command not found\n", data->cmd->arg[0]); // to do zmiany
		ft_free2d(envp);
		exit(127);
	}
	if (execve(path, data->cmd->arg, envp) < 0) // to też
	{
		free(path);
		ft_free2d(envp);
		exit(126);
	}
}

void	exec_child_builtin(t_data *data, t_envp *env)
{
	if (!ft_strcmp(data->cmd->arg[0], "echo"))
		exit(ft_echo(data->cmd->arg));
	else if (!ft_strcmp(data->cmd->arg[0], "env"))
		exit(ft_env(data->cmd->arg, env));
	else if (!ft_strcmp(data->cmd->arg[0], "pwd"))
		exit(ft_pwd(env));
	exit(0);
}

void	exec_simple_command(t_data *data, t_envp *env)
{
	pid_t pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (redirections(data) < 0)
			exit (1);
		if (is_child_builtin(data->cmd->arg[0]))
			exec_child_builtin(data, env);
		exec_external(data, env);
	}
	else if (pid < 0)
	{
		perror("fork");
		data->ls_exit = 1;
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->ls_exit = WEXITSTATUS(status);
	else
		data->ls_exit = 1;
	return ;
}