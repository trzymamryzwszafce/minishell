/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:15:58 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/18 19:21:51 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **args, t_envp *list)
{
	if (args[1])
	{
		ft_putendl_fd("bash: env: za duzo argumenow\n", 2);
		return (1);
	}
	while (list)
	{
		if (list->value != NULL)
		{
			ft_printf("%s=", list->key);
			ft_printf("%s\n", list->value);
		}
		list = list->next;
	}
	return (0);
}
