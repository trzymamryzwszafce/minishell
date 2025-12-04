#include "../minishell.h"

void	free_int_array(int *arr, int size)
{
	(void)size;
	if (arr)
		free(arr);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd->arg)
		ft_free_str_array(cmd->arg);
	if (cmd->red_out)
		ft_free_str_array(cmd->red_out);
	if (cmd->red_in)
		ft_free_str_array(cmd->red_in);
	if (cmd->heredoc)
	{
		i = 0;
		while (i < cmd->heredoc_count)
		{
			free(cmd->heredoc[i]);
			i++;
		}
		free(cmd->heredoc);
	}
	if (cmd->heredoc_tmp)
		free_int_array(cmd->heredoc_tmp, cmd->heredoc_count);
	free(cmd);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd)
	{
		ft_free_command_list(data->cmd);
		data->cmd = NULL;
	}
}