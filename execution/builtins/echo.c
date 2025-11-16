/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:10:14 by szmadeja          #+#    #+#             */
/*   Updated: 2025/11/16 18:22:20 by szmadeja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	j;
	int	nline;

	i = 1;
	nline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		nline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (nline == 1)
		ft_printf("\n");
}
