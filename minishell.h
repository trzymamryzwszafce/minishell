/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szmadeja <szmadeja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:49:36 by sorbi             #+#    #+#             */
/*   Updated: 2025/12/04 11:17:36 by szmadeja         ###   ########.fr       */
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
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_convert
{
	bool double_q;
	bool single_q;
	struct s_envp **envp;
}	t_convert;

typedef enum s_type
{
	R_IN,		// <
	ARG_IN,
	R_OUT_TRUNC,	// >
	ARG_OUT,
	R_OUT_APP,	// >>
	R_HEREDOC,	// <<
	PIPE,		// |
	ARG,		// cmd, args, flags, envp
	HEREDOC_DELI,
}		t_type;

typedef struct s_token
{
	char			*elem;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}		t_token;

typedef struct s_pipes
{
	int	fd[2];
	int	old_fd;
}	t_pipes;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_command
{
	char	**arg;
	char	**red_out;
	char	**red_in;
	bool	append;
	char	**heredoc;
	bool	b_heredoc;
	int		heredoc_count;
	int		*heredoc_tmp;
	struct s_command *next;
}		t_command;

typedef struct s_data
{
	int cmd_count;
	int	ls_exit;
	int	pipe_count;
	t_command *cmd;
}	t_data;

//main.c
void	init_cmd(t_command *cmd);
int	ft_parsing(t_token *tokens, t_envp **envp, char *input,  int error, t_data *data);
void	ft_process_input(char *input, t_envp **envp);

//free_structs.c
void	ft_free_str_array(char **arr);
void	ft_free_command_list(t_command *cmd);
void	ft_free_env_list(t_envp **envp);
void	ft_free_tokens(t_token *tokens);

int		ft_count_until_deli(char *s, int n, char delimiter, int count);
void	init_cmd(t_command *cmd);

//splitting_args.c
int		ft_split_input(t_token *tokens, char *input);
int	ft_check_syntax_errors(char *input, int input_len);
t_token	*ft_is_limiter(t_token *token, char *input, int *i);
t_token	*ft_quote(t_token *token, char *input, char deli, int *i);
int		ft_count_chars(char *s, int n);

//splitting_args2.c
int	ft_skip_quotes(char *s, int *n);
t_token	*ft_add_node(t_token *token, char *s, int *i, int n);
t_token	*ft_create_node(t_token *cur);
int		ft_count_input_words(char const *s);

//tokenizer.c
void	ft_add_type(t_token *token);
void ft_add_type_arg(t_token *token);

//envp.c
t_envp	*ft_create_envp(char **environ);
void ft_add_to_envp(t_envp **envp, char *key, char *value);
void ft_new_envp_value(t_envp **envp, char *key, char *value);
char *ft_get_envp_value(t_envp **envp, char *key);

//envp2.c
void ft_add_envp_list(t_envp **envp, char *key, char *value);
char *ft_assign_value(char *str);
char *ft_assign_key(char *str);

//error.c
int ft_errors(t_token *token);
int	ft_check_redir(t_token *cur, int *error, char **message);
int	ft_check_pipe(t_token *cur, int i, int *error, char **message);
void	ft_check_quotes(t_token *cur, int *error, char **message);
void    ft_error_message(int exit_code, char *message);

//error2.c
int ft_quote_error(char *s);
int ft_pipe_error(int position, char *current, char *next);
int ft_redir_error(enum s_type cur_type, enum s_type next_type);
int ft_type_input(t_token *token, t_envp **envp, t_data *data);

//arg_converter.c
void ft_arg_converter(t_token *token, t_envp **envp, t_data *data);
char *ft_convert(t_token str, t_envp **envp, t_convert *sign);
char *ft_envp_value_converter(t_envp **envp, char *str, int *i, char *new_str);
char *ft_handle_double_quote(char *str, t_convert *sign, int *i, char *new_str);
char *ft_handle_single_quote(char *str, t_convert *sign, int *i, char *new_str);

//arg_converter2.c
char *ft_change_arg(char *str, t_convert *sign, int *i, char *new_str);
char *ft_double_quote(char *str, int *i, char *new_str, t_envp **envp);
char *ft_no_quote(char *str, t_convert *sign, int *i, char *new_str);
char *ft_join_and_free(char *s1, char *s2);
char	*ft_substr_join_free(char *new_str, char *str, int start, int len);

//struct_filler.c
void ft_struct_filler(t_token *tokens, t_data *data);

//typer.c
void	count_and_alloc_for_cmd(t_token *start, t_command *cmd);

//debug.c
void print_command_list(t_command *cmd);

void	execution(t_data *data, t_envp **env, t_token *tokens);

//builtins
int	ft_cd(t_envp **env, char **args);
int	ft_echo(char **args);
int	ft_env(char **args, t_envp *list);
int	ft_exit(char **args, int last_status);
int	ft_export(t_envp **env, char **args);
int	ft_pwd(t_envp *env);
int	ft_unset(t_envp **env, char **args);
//utils
int	valid_check(char *s);
int	print_expo_env(t_envp *env);
void	env_update(t_envp **env, char *key, char *value);
int	is_builtin(char *cmd);
void	env_add(t_envp **env, char *key, char *value);
int	is_parent_builtin(char *cmd);
int	is_child_builtin(char *cmd);
void execute_builtin(t_data *data, t_envp **env);
char	*search_path(char **dirs, char *cmd);
char	*cmd_path(char *cmd, char **envp);
char	**list_to_arr(t_envp *env);
char	*cmd_path(char *cmd, char **envp);
char	*path_check(char *dir, char *cmd);
char	**get_path(char **envp);
void	exec_simple_command(t_data *data, t_envp *env, t_token *tokens);
int	redirections(t_data *data);
int	process_heredoc(char **heredoc, int heredoc_count);
void	exec_pipeline(t_data *data, t_envp **env);
void	exec_child_builtin(t_data *data, t_envp *env, t_token *tokens);
int	exec_parent_builtin(t_data *data, t_envp **env);
void	exec_external(t_data *data, t_envp *env);
void	exec_signals(void);
void	idle_signals(void);
void	free_data(t_data *data);

#endif
