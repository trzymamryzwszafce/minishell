#include "../minishell.h"

int	write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

int	create_heredoc_file(char *delimeter)
{
	int	fd;

	fd = open("/tmp/.heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	write_heredoc(fd, delimeter);
	close(fd);
	return (0);
}

int	process_heredoc(char **heredoc, int heredoc_count)
{
	int					i;
	struct sigaction	sa;

	if (!heredoc || heredoc_count == 0)
		return (0);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	i = 0;
	while (i < heredoc_count)
	{
		if (create_heredoc_file(heredoc[i]) < 0)
			return (-1);
		i++;
	}
	idle_signals();
	return (0);
}
