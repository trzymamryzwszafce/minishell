#include "../minishell.h"

static void	handle_builtin_in_pipe(t_data *data, t_envp **env)
{
	if (is_child_builtin(data->cmd->arg[0]))
		exec_child_builtin(data, *env);
	else
	{
		data->ls_exit = exec_parent_builtin(data, env);
		exit_with_cleanup(data, *env, data->ls_exit);
	}
}

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
		exit_with_cleanup(data, *env, 1);
	if (is_builtin(data->cmd->arg[0]))
		handle_builtin_in_pipe(data, env);
	exec_external(data, *env);
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

static void	handle_pipe_child(t_data *data, t_pipes *pipes, t_envp **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_pipe(data, pipes, env);
}

static void	cleanup_pipes(t_pipes *pipes)
{
	if (pipes->old_fd != STDIN_FILENO)
		close(pipes->old_fd);
}

static int	init_pipe(t_data *data, t_pipes *pipes)
{
	if (data->cmd->next && pipe(pipes->fd) == -1)
	{
		cleanup_pipes(pipes);
		perror("pipe");
		data->ls_exit = 1;
		return (-1);
	}
	return (0);
}

static int	fork_child(t_data *data, t_pipes *pipes, t_envp **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		cleanup_pipes(pipes);
		perror("fork");
		data->ls_exit = 1;
		return (-1);
	}
	if (pid == 0)
		handle_pipe_child(data, pipes, env);
	return (0);
}

void	exec_pipeline(t_data *data, t_envp **env)
{
	t_pipes		pipes;
	t_command	*start;

	if (prepipe_heredoc(data) < 0)
		return ((void)(data->ls_exit = 1));
	exec_signals();
	pipes.old_fd = STDIN_FILENO;
	start = data->cmd;
	while (data->cmd)
	{
		if (init_pipe(data, &pipes) < 0)
			return ;
		if (fork_child(data, &pipes, env) < 0)
			return ;
		update_pipes(data, &pipes);
		data->cmd = data->cmd->next;
	}
	dziecko_czekanie(data);
	data->cmd = start;
	idle_signals();
}

// void	handle_pipe(t_data *data, t_pipes *pipes, t_envp **env)
// {
// 	if (pipes->old_fd != STDIN_FILENO)
// 	{
// 		dup2(pipes->old_fd, STDIN_FILENO);
// 		close(pipes->old_fd);
// 	}
// 	if (data->cmd->next)
// 	{
// 		close(pipes->fd[0]);
// 		dup2(pipes->fd[1], STDOUT_FILENO);
// 		close(pipes->fd[1]);
// 	}
// 	if (redirections(data) < 0)
// 		exit(data->ls_exit = 1);
// 	if (is_builtin(data->cmd->arg[0]))
// 	{
// 		if (is_child_builtin(data->cmd->arg[0]))
// 			exec_child_builtin(data, *env);
// 		else
// 			exit (data->ls_exit = exec_parent_builtin(data, env));
// 	}
// 	exec_external(data, *env);
// 	exit(data->ls_exit = 127);
// }

// void	update_pipes(t_data *data, t_pipes *pipes)
// {
// 	if (pipes->old_fd != STDIN_FILENO)
// 		close(pipes->old_fd);
// 	if (data->cmd->next)
// 	{
// 		close(pipes->fd[1]);
// 		pipes->old_fd = pipes->fd[0];
// 	}
// }

// void	dziecko_czekanie(t_data *data)
// {
// 	int	status;
// 	int	sig;

// 	while (wait(&status) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			data->ls_exit = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 		{
// 			sig = WTERMSIG(status);
// 			if (sig == SIGINT)
// 				write(2, "\n", 1);
// 			else if (sig == SIGQUIT)
// 				write(2, "Quit: (core dumped)\n", 20);
// 			data->ls_exit = 128 + sig;
// 		}
// 	}
// }

// int	prepipe_heredoc(t_data *data)
// {
// 	t_command	*start;

// 	start = data->cmd;
// 	while (data->cmd)
// 	{
// 		if (data->cmd->heredoc_count > 0)
// 		{
// 			if (process_heredoc(data->cmd->heredoc,
// 					data->cmd->heredoc_count) < 0)
// 			{
// 				data->cmd = start;
// 				return (-1);
// 			}
// 		}
// 		data->cmd = data->cmd->next;
// 	}
// 	data->cmd = start;
// 	return (0);
// }

// void	exec_pipeline(t_data *data, t_envp **env)
// {
// 	t_pipes		pipes;
// 	pid_t		pid;
// 	t_command	*start;

// 	if (prepipe_heredoc(data) < 0)
// 		return ((void)(data->ls_exit = 1));
// 	exec_signals();
// 	pipes.old_fd = STDIN_FILENO;
// 	start = data->cmd;
// 	while (data->cmd)
// 	{
// 		if (data->cmd->next && pipe(pipes.fd) == -1)
// 			return (perror("pipe"), (void)(data->ls_exit = 1));
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("fork"), (void)(data->ls_exit = 1));
// 		if (pid == 0)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			signal(SIGQUIT, SIG_DFL);
// 			handle_pipe(data, &pipes, env);
// 		}
// 		update_pipes(data, &pipes);
// 		data->cmd = data->cmd->next;
// 	}
// 	dziecko_czekanie(data);
// 	data->cmd = start;
// }