/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:58:05 by szmadeja          #+#    #+#             */
/*   Updated: 2025/10/15 21:41:49 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	exec_external(t_pipeline *args)
{
	pid_t	pid;

	pid = fork();
	if (pid = 0)
	{
		execve(args->cmds->cmd[0], args->cmds->cmd, args->envp);
		exit(1);
	}
	else if (pid > 0)
		wait(NULL);
}

void	(t_pipeline *args)
{
	if (is_builtin(args->cmds->cmd))
		exec_builtin(args);
	else
		exec_external(args);
}
*/