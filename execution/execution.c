/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:19:42 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/05 21:54:30 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_parent_builtin(t_data *data, t_envp **env)
{
	if (!ft_strcmp(data->cmd->arg[0], "cd"))
		return (ft_cd(env, data->cmd->arg));
	else if (!ft_strcmp(data->cmd->arg[0], "export"))
		return (ft_export(env, data->cmd->arg));
	else if (!ft_strcmp(data->cmd->arg[0], "unset"))
		return (ft_unset(env, data->cmd->arg));
	else if (!ft_strcmp(data->cmd->arg[0], "exit"))
		return (ft_exit(data->cmd->arg, data, *env));
	return (0);
}

void	restore_fd(int fd_in, int fd_out)
{
	if (fd_in >= 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out >= 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	execution(t_data *data, t_envp **env)
{
	int	fd_in;
	int	fd_out;

	if (data->pipe_count == 0 && is_parent_builtin(data->cmd->arg[0]))
	{
		fd_in = dup(STDIN_FILENO);
		fd_out = dup(STDOUT_FILENO);
		if (redirections(data) < 0)
		{
			data->ls_exit = 1;
			return (restore_fd(fd_in, fd_out));
		}
		data->ls_exit = exec_parent_builtin(data, env);
		return (restore_fd(fd_in, fd_out));
	}
	if (data->cmd->next)
		exec_pipeline(data, env);
	else
		exec_simple_command(data, *env);
}
