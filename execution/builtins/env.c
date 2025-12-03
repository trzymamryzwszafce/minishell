/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:15:58 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/03 01:44:45 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **args, t_envp *list)
{
	if (args[1])
	{
		ft_putendl_fd("bash: env: too much arguments\n", 2);
		return (1);
	}
	while (list)
	{
		if (list->value != NULL)
		{
			ft_putstr_fd(list->key, 2);
			ft_putstr_fd("=", 2);
			ft_putendl_fd(list->value, 2);
		}
		list = list->next;
	}
	return (0);
}
