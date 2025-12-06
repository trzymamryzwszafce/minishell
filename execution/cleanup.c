/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 01:49:11 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/06 01:53:53 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (data)
		free(data);
}

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
