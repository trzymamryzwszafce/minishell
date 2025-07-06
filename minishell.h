/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:22:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/07/06 23:53:24 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE '|'

typedef struct s_lexer
{
	char *command;
	char *flag;
	char *argument;
	char *type; //pipe, redirection, etc
	struct s_lexer *next; //lista żeby przechodzć pomiędzy poprzednią i następną komendą
	
}	t_lexer;

typedef struct s_mini
{
	//wszystkie argumenty
	char **arg_list;
	t_lexer *lexer;
	
}	t_mini;

//parsing
void ft_split_input(t_mini *arguments, char *input);
void ft_lexer(t_mini *arguments);

int	ft_count_words(char **array);
#endif
