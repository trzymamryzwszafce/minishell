#include "minishell.h"
//to wszystko jako debuger to zniknie za jakiś czas
char *ft_dupa(enum s_type dupa)
{
	switch (dupa)
	{
		case R_IN : return "r_in";
		case R_OUT_TRUNC : return "r_out_trunc";
		case R_OUT_APP : return "r_out_app";
		case R_HEREDOC : return "heredoc";
		case PIPE : return "pipe";
		case ARG : return "arg";
		case ARG_IN : return "arg_in";
		case ARG_OUT : return "arg_out";
	}
	return (NULL);
}
static void free_str_array(char **arr)
{
    int i;
	
	i = 0;
    if (!arr)
        return ;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void ft_free_command_list(t_command *cmd)
{
    t_command *tmp;

    while (cmd)
    {
        tmp = cmd->next;

        free_str_array(cmd->arg);
        free_str_array(cmd->red_in);
        free_str_array(cmd->red_out);
        free_str_array(cmd->heredoc);

        free(cmd);
        cmd = tmp;
    }
	//free(cmd);
}

void ft_free_env_list(t_envp **envp)
{
    t_envp *tmp;

    while (*envp)
    {
        tmp = (*envp)->next;
        free((*envp)->key);
        free((*envp)->value);
		free(*envp);
        *envp = tmp;
    }
}

/* free whole token linked list (elem + node) */
void ft_free_tokens(t_token *tokens)
{
	t_token *cur;
	t_token *tmp;

	cur = tokens;
	while (cur)
	{
		tmp = cur->next;
		if (cur->elem)
			free(cur->elem);
		free(cur);
		cur = tmp;
	}
}

int ft_parsing(t_token *tokens, t_envp **envp, char *input,  int error)
{
	error = ft_split_input(tokens, input);
	if (error == 0)
		error = ft_type_input(tokens, envp);
	return (error);
}
void ft_process_input(char *input, t_envp **envp)
{
	t_token *tokens;
	t_data *data;
	t_command *cmd;
	int error;

	add_history(input);
	tokens = ft_calloc(1, sizeof(t_token));
	data = ft_calloc(1, sizeof(t_data));
	data->cmd = NULL;
	error = ft_parsing(tokens, envp, input, 0);
	if (error == 0)
		ft_struct_filler(tokens, data);
	// for (t_token *p = tokens; p; p = p->next) {
	// 		printf("node: %s\n", p->elem ? p->elem : "(null)");
	// 		printf("type: %s\n", ft_dupa(p->type) ? ft_dupa(p->type) : "(null)");
	// 		}
	if (error == 0)
	{
		print_command_list(data->cmd);
		//egzekuzja
		ft_free_command_list(data->cmd);
    	data->cmd = NULL;
	}
	ft_free_tokens(tokens);
	free(data);
}


int	main(void)
{
	extern char **environ;
 	char *input;
	t_envp *envp;
	using_history();
	envp = ft_create_envp(environ);
	while (1)
	{
		input = readline(">>> ");
		if (!input)
			break ;
		else if (*input)
			ft_process_input(input, &envp);
		free(input);
	}
	ft_free_env_list(&envp);
	rl_clear_history();
	return (0);
}
