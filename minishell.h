/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:22:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/07/07 23:58:31 by sorbi            ###   ########.fr       */
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
	char **params;
	char **type;
	char **redir_targets;
	struct s_lexer *next; //lista żeby przechodzć pomiędzy poprzednią i następną komendą
	
}	t_lexer;

typedef struct s_mini
{
	char **arg_list; //wszystkie argumenty
	t_lexer *lexer;
	
}	t_mini;

//parsing
void ft_split_input(t_mini *arguments, char *input);
void ft_lexer(t_mini *arguments);

int	ft_count_words(char **array);
void ft_null_lexer(t_lexer *cmd_line);
int ft_is_cmd(char *cmd);
char **ft_copy_args(char **arg_list, int start, int count);
int ft_is_redirect(char *token);
int ft_is_pipe(char *token);
char **add_to_str_array(char **array, char *str);
int ft_count_args(char **args);
#endif
