/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:14:56 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/24 05:53:08 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_envp *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			ft_printf("%s\n", env->value);
			return (0);
		}
		env = env->next;
	}
	return (1);

	// char	*cwd;

	// cwd = getcwd(NULL, 0);
	// if (!cwd)
	// {
	// 	perror("pwd");
	// 	return (1);
	// }
	// ft_putendl_fd(cwd, 1);
	// free(cwd);
	// return (0);
}
