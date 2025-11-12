/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 21:58:05 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/12 21:53:12 by szmadeja         ###   ########.fr       */
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
*/
