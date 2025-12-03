/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:10:14 by szmadeja          #+#    #+#             */
/*   Updated: 2025/12/03 17:48:49 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_n_flag(char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

int	ft_echo(char **args)
{
	int	i;
	int	nline;

	i = 1;
	nline = 1;
	while (args[i] && check_n_flag(args[i]))
	{
		nline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 2);
		if (args[i + 1])
			ft_putstr_fd(" ", 2);
		i++;
	}
	if (nline)
		ft_putendl_fd("", 2);
	return (0);
}
