/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:14:56 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/03 01:54:20 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_envp *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			ft_putendl_fd(env->value, 2);
			return (0);
		}
		env = env->next;
	}
	return (1);
}
