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
		exit(1);
	if (is_builtin(data->cmd->arg[0]))
	{
		if (is_child_builtin(data->cmd->arg[0]))
		{
			exec_child_builtin(data, *env);
			exit (data->ls_exit);
		}
		else
			exit(exec_parent_builtin(data, env));
	}
	exec_external(data, *env);
	exit(127);
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
	
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			data->ls_exit = WEXITSTATUS(status);
		else
			data->ls_exit = 1;
	}
}

void	exec_pipeline(t_data *data, t_envp **env)
{
	t_pipes	pipes;
	pid_t	pid;

	pipes.old_fd = STDIN_FILENO;
	while (data->cmd)
	{
		if (data->cmd->next && pipe(pipes.fd) == -1)
			return (perror("pipe"), (void)(data->ls_exit = 1));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), (void)(data->ls_exit = 1));
		if (pid == 0)
			handle_pipe(data, &pipes, env);
		update_pipes(data, &pipes);
		data->cmd = data->cmd->next;
	}
	dziecko_czekanie(data);
}
