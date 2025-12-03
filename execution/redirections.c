#include "../minishell.h"

int	handle_input_redirs(char **red_in)
{
	int	fd;
	int	i;

	if (!red_in)
		return (0);
	i = 0;
	while (red_in[i])
	{
		fd = open(red_in[i], O_RDONLY);
		if (fd < 0)
		{
			perror(red_in[i]);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int	handle_output_redirs(char **red_out, bool append)
{
	int	fd;
	int	i;
	int	flags;

	if (!red_out)
		return (0);
	i = 0;
	while (red_out[i])
	{
		if (append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(red_out[i], flags, 0644);
		if (fd < 0)
		{
			perror(red_out[i]);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int	apply_heredoc(void)
{
	int	fd;

	fd = open("/tmp/.heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("/tmp/.heredoc_tmp");
	return (0);
}

void	cleanup(void)
{
	unlink ("/tmp/.heredoc_tmp");
}

int	redirections(t_data *data)
{
	if (!data->cmd)
		return (0);
	if (data->cmd->b_heredoc)
	{
		if (apply_heredoc() < 0)
			return (cleanup(), -1);
	}
	else if (handle_input_redirs(data->cmd->red_in) < 0)
		return (cleanup(), -1);
	if (handle_output_redirs(data->cmd->red_out, data->cmd->append) < 0)
		return (cleanup(), -1);
	if (data->cmd->heredoc_count > 0)
		cleanup();
	return (0);
}
