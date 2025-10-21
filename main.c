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
		//case ENV : return "env";
	}
	return (NULL);
}

// for (t_token *p = tokens; p; p = p->next) {
// 				printf("node: %s\n", p->elem ? p->elem : "(null)");
// 				printf("type: %s\n", ft_dupa(p->type) ? ft_dupa(p->type) : "7");
// 			}


int ft_parsing(t_token *tokens, char *input,  int error)
{
	error = ft_split_input(tokens, input);
	if (error == 0)
		error = ft_type_input(tokens);
	return (error);
}
void ft_process_input(char *input)
{
	t_token *tokens;
	int error;

	add_history(input);
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return ;
	error = ft_parsing(tokens, input, 0);
	if (error == 0)
	{
		//egzekucja
	}
	free(tokens);
}

int	main(void)
{
	extern char **environ;
 	char *input;
	using_history();
	ft_create_envp(environ);
	while (1)
	{
		input = readline(">>> ");
		if (!input)
			return (0);
		else if (*input)
			ft_process_input(input);
		free(input);
	}
	rl_clear_history(); //czyścimy historie z >>> - nie wiem czy potrzebne
	return (0);
}
