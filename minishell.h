/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:22:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/07/23 02:15:25 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer
{
	char	*command;
	char	*flag;
	char	**params;
	char	**type;
	char	**redir_targets;
	struct	s_lexer *next;
}		t_lexer;

typedef struct s_mini
{
	char	**arg_list; //wszystkie argumenty
	t_lexer	*lexer;	
}		t_mini;

//lexer.c
int		ft_process_command(t_lexer *cmd_line, char **args, int *i);
void	ft_process_arguments(t_lexer *cmd_line, char **args, int *i);
int		ft_process_redirects(t_lexer *cmd_line, char **args, int *i);
void	ft_lexer(t_mini *arguments);

//lexer_utils.c
t_lexer	*ft_create_next_node(t_lexer *current);
void	ft_null_lexer(t_lexer *cmd_line);
int		ft_is_redirect(char *token);
int		ft_is_pipe(char *token);

//parsing.c
int		ft_count_args(char **args);
char	**ft_copy_args(char **arg_list, int start, int count);
char	**add_to_str_array(char **array, char *str);
void	ft_split_input(t_mini *arguments, char *input);
#endif
