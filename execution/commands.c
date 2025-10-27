/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:58:05 by szmadeja          #+#    #+#             */
/*   Updated: 2025/10/20 19:55:24 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	exec_external(void)
{
	pid_t	pid;
	char	*argv[] = {"/bin/ls", "-l", NULL};
	char	*envp[] = {NULL};

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, envp);
		exit(1);
	}
	else if (pid > 0)
		wait(NULL);
}

void	(t_command *args)
{
	if (is_builtin(args->cmds->cmd))
		exec_builtin(args);
	else
		exec_external(args);
}
*/
