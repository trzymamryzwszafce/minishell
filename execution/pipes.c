/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 01:38:12 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/06 01:48:40 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe(t_data *data, t_pipes *pipes, t_envp **env)
{
	if (pipes->old_fd != STDIN_FILENO)
	{
		dup2(pipes->old_fd, STDIN_FILENO);
		close(pipes->old_fd);
	}
	if (data->cmd->next)
	{
		close(pipes->fd[0]);
		dup2(pipes->fd[1], STDOUT_FILENO);
		close(pipes->fd[1]);
	}
	if (redirections(data) < 0)
		exit(data->ls_exit = 1);
	if (is_builtin(data->cmd->arg[0]))
	{
		if (is_child_builtin(data->cmd->arg[0]))
			exec_child_builtin(data, *env);
		else
			exit (data->ls_exit = exec_parent_builtin(data, env));
	}
	exec_external(data, *env);
	exit(data->ls_exit = 127);
}

void	update_pipes(t_data *data, t_pipes *pipes)
{
	if (pipes->old_fd != STDIN_FILENO)
		close(pipes->old_fd);
	if (data->cmd->next)
	{
		close(pipes->fd[1]);
		pipes->old_fd = pipes->fd[0];
	}
}

void	dziecko_czekanie(t_data *data)
{
	int	status;
	int	sig;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			data->ls_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(2, "\n", 1);
			else if (sig == SIGQUIT)
				write(2, "Quit: (core dumped)\n", 20);
			data->ls_exit = 128 + sig;
		}
	}
}

int	prepipe_heredoc(t_data *data)
{
	t_command	*start;

	start = data->cmd;
	while (data->cmd)
	{
		if (data->cmd->heredoc_count > 0)
		{
			if (process_heredoc(data->cmd->heredoc,
					data->cmd->heredoc_count) < 0)
			{
				data->cmd = start;
				return (-1);
			}
		}
		data->cmd = data->cmd->next;
	}
	data->cmd = start;
	return (0);
}

void	exec_pipeline(t_data *data, t_envp **env)
{
	t_pipes		pipes;
	pid_t		pid;

	if (prepipe_heredoc(data) < 0)
		return ((void)(data->ls_exit = 1));
	exec_signals();
	pipes.old_fd = STDIN_FILENO;
	while (data->cmd)
	{
		if (data->cmd->next && pipe(pipes.fd) == -1)
			return (perror("pipe"), (void)(data->ls_exit = 1));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), (void)(data->ls_exit = 1));
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			handle_pipe(data, &pipes, env);
		}
		update_pipes(data, &pipes);
		data->cmd = data->cmd->next;
	}
	dziecko_czekanie(data);
}
