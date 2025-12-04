/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:58:05 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/04 16:00:01 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_child(t_data *data, t_envp *env, t_token *tokens)
{
	free_data(data);
	ft_free_env_list(&env);
	ft_free_tokens(tokens);
}

void	exit_with_cleanup(t_data *data, t_envp *env, int code)
{
	data->ls_exit = code;
	cleanup_child(data, env, data->token);
	exit(code);
}

static void	handle_execve_error(char *path, char **envp, t_data *data,
		t_envp *env)
{
	perror(path);
	free(path);
	ft_free2d(envp);
	exit_with_cleanup(data, env, 126);
}

void	exec_external(t_data *data, t_envp *env)
{
	char	**envp;
	char	*path;

	if (!data->cmd->arg || !data->cmd->arg[0])
		exit_with_cleanup(data, env, 127);
	envp = list_to_arr(env);
	if (!envp)
		exit_with_cleanup(data, env, 1);
	path = cmd_path(data->cmd->arg[0], envp);
	if (!path)
	{
		ft_putstr_fd(data->cmd->arg[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free2d(envp);
		exit_with_cleanup(data, env, 127);
	}
	execve(path, data->cmd->arg, envp);
	handle_execve_error(path, envp, data, env);
}

void	exec_child_builtin(t_data *data, t_envp *env)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(data->cmd->arg[0], "echo"))
		exit_code = ft_echo(data->cmd->arg);
	else if (!ft_strcmp(data->cmd->arg[0], "env"))
		exit_code = ft_env(data->cmd->arg, env);
	else if (!ft_strcmp(data->cmd->arg[0], "pwd"))
		exit_code = ft_pwd(env);
	data->ls_exit = exit_code;
	cleanup_child(data, env, data->token);
	exit(exit_code);
}

void	wait_child(t_data *data, pid_t pid)
{
	int	status;
	int	sig;

	waitpid(pid, &status, 0);
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

int	prefork_heredoc(t_data *data)
{
	if (data->cmd->heredoc_count > 0)
	{
		if (process_heredoc(data->cmd->heredoc, data->cmd->heredoc_count) < 0)
		{
			data->ls_exit = 1;
			return (-1);
		}
	}
	return (0);
}

static void	handle_child_process(t_data *data, t_envp *env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (redirections(data) < 0)
		exit_with_cleanup(data, env, 1);
	if (is_child_builtin(data->cmd->arg[0]))
		exec_child_builtin(data, env);
	exec_external(data, env);
}

void	exec_simple_command(t_data *data, t_envp *env)
{
	pid_t	pid;

	if (prefork_heredoc(data) < 0)
		return ;
	exec_signals();
	pid = fork();
	if (pid == 0)
		handle_child_process(data, env);
	else if (pid < 0)
	{
		perror("fork");
		data->ls_exit = 1;
		return ;
	}
	wait_child(data, pid);
	idle_signals();
}
