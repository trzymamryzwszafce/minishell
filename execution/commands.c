/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:58:05 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/22 19:39:11 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	exec_simple_command(t_data *data, t_command *cmd, t_envp *env)
// {
// 	pid_t pid;

// 	pid = fork();
// 	//if (data->cmd = 1)
// 	if (pid == 0)
// 	{
// 		//redirections(data) TODO
// 		exec_single_command(data, cmd, env);
// 	}
// 	else if (pid < 0)
// 	{
// 		perror("fork");
// 	}
// 	waitpid(pid, &status, 0);
// 	return ;
// }