/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:19:42 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/21 03:51:30 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_data *data, t_command *cmd, t_envp **env)
{
	if (data->pipe_count == 0 && data->cmd_count == 1
		&& !ft_strcmp(cmd->arg[0], "exit"))
		ft_exit(cmd->arg[0], data->ls_exit);
	exec_cmd(data, cmd, env);
}
