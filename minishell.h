/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:22:38 by szmadeja          #+#    #+#             */
/*   Updated: 2025/07/28 00:50:07 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>

typedef struct s_lexer
{
	char	*command;
	char	*flag;
	char	**params;
	char	**type; //na odpowiednim miejscu w array dla danego redirect jest zapisany plik do którego to ma isc
	char	**redir_targets;
	char	**envp;
	struct	s_lexer *next;
}		t_lexer;

typedef enum s_redir_type
{
    R_IN,        // <
    R_OUT_TRUNC, // >
    R_OUT_APP,   // >>
    R_HEREDOC    // <<
}		t_redir_type;

typedef struct s_redir
{
    t_redir_type type;
    char         *target;   // nazwa pliku / limiter heredoca
}		t_redir;

typedef struct s_command
{
	char	*cmd; //cmd, flags, args - ostatni cmd[] == NULL
	int		argc; //nie wiem czy tu zostanie 
	t_redir	*redir;
	int		redir_count;
	int		in_fd;
    int		out_fd; //nad tymi dwoma jeszcze myśle
	char	*heredoc_tmp; //wypierdala - bool
    int		heredoc_fd;
}		t_command; //jeżeli będzie kolejna to oznacza że jest pipe 

typedef struct s_pipeline
{
    t_command	*cmds;
    int			cmd_count;
    char		**envp;
    int			last_exit_status;
    bool		parse_error;
}		t_pipeline;

typedef struct s_mini
{
	char	**arg_list; //wszystkie argumenty
	t_lexer	*lexer;	
	t_pipeline	*cmd_line;
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
int 	ft_count_only_args(char **args, int *i);
char	**ft_copy_args(char **arg_list, int start, int count);
char	**add_to_str_array(char **array, char *str);
void	ft_split_input(t_mini *arguments, char *input);

#endif
