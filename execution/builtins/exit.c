/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:16:26 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/03 23:43:50 by szmadeja         ###   ########.fr       */
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

int	ft_exit(char **args, int last_status)
{
	long long	status;

	ft_putstr_fd("exit\n", 2);
	if (!args[1])
		exit(last_status);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		exit (2);
	}
	if (args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	status = ft_atoll(args[1]);
	exit ((unsigned char)status);
}
