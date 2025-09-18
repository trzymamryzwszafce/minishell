/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:22:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/09/06 21:49:36 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>

typedef enum s_type
{
	R_IN,		// <
	R_OUT_TRUNC,	// >
	R_OUT_APP,	// >>
	R_HEREDOC,	// <<
	PIPE,		// |
	ARG,	

}		t_type;

typedef struct s_token
{
	char *elem;
	t_type type;
	struct s_token *next;
}		t_token;

typedef struct s_lexer
{
	char	*command;
	char	*flag;
	char	**params;
	char	**type; //na odpowiednim miejscu w array dla danego redirect jest zapisany plik do którego to ma isc
	char	**redir_targets;
	struct	s_lexer *next;
}		t_lexer;



//to oddam szymonowi

typedef struct s_command
{
	char	**cmd; //cmd, args, flags - ostatni cmd[] == NULL
	char	**red_out;
	char	**red_in;
	bool	append;
	char	*pipe_out; //(może jako bool)jak nie ma pipe to jest NULL jeśli jest to execve bierze input jako output albo na odwrót chuj wie
	bool	redir;
}		t_command; //jeżeli będzie kolejna to oznacza że jest pipe 

typedef struct s_pipeline
{
	t_command	*cmds;
	int	cmd_count;
	char	*binary; //pliki do sprawdzenia czy się otwierają
	char	*heredoc;
	char	**envp; //to jako normalnie lista osobnych env
}		t_pipeline;



typedef struct s_mini
{
	char	**arg_list; //wszystkie argumenty
	t_lexer	*lexer;	
	t_pipeline	*cmd_line;
}		t_mini;

//main.c 

void	ft_split_input(t_token *tokens, char *input);


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
int 	ft_count_only_args(char **args, int *i);
char	**ft_copy_args(char **arg_list, int start, int count);
char	**add_to_str_array(char **array, char *str);

#endif
