/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:16:26 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/16 20:27:59 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args, int last_status)
{
	long long	code;

	ft_printf("exit\n");
	if (!args[1])
		exit(last_status);
	if (!is_numeric(args[1]))
	{
		ft_printf("bash: exit: %s: daj numerki\n", args[1]);
		exit (2);
	}
	if (args[2])
	{
		ft_printf("bash: exit: za duzo argumentuw\n");
		return ;
	}
	code = ft_atoll(args[1]);
	exit ((unsigned char)code);
}
