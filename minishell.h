/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorbi <sorbi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:49:36 by sorbi             #+#    #+#             */
/*   Updated: 2025/10/23 17:52:55 by sorbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>

typedef enum s_type
{
	R_IN,		// <
	R_OUT_TRUNC,	// >
	R_OUT_APP,	// >>
	R_HEREDOC,	// <<
	PIPE,		// |
	ARG,		// cmd, args, flags
	//ENV,		// envp
}		t_type;

typedef struct s_token
{
	char			*elem;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}		t_token;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_command
{
	char	**cmd;
	char	**red_out;
	char	**red_in;
	bool	append;
	bool	*pipe_out;
	bool	redir;
	int		cmd_count;
	char	*binary;
	char	*heredoc;
	t_envp	**envp;
}		t_command;

//splitting_args.c
int		ft_count_input_words(char const *s);
t_token	*ft_create_node(t_token *cur);
t_token	*ft_add_node(t_token *token, char *s, int *i, int n);
int		ft_count_chars(char *s, int n);
t_token	*ft_quote(t_token *token, char *input, char deli, int *i);
t_token	*ft_is_limiter(t_token *token, char *input, int *i);
int		ft_split_input(t_token *tokens, char *input);

int		ft_count_until_deli(char *s, int n, char delimiter, int count);

//tokenizer.c
int		ft_type_input(t_token *token);
void	ft_add_type(t_token *token);
void	ft_is_redir_pipe(t_token *token);

void	ft_error_message(int exit_code, char *message);

//envp.c
t_envp	*ft_create_envp(char **environ);

#endif
