#include "minishell.h"

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


int	main(void)
{
 	char *input;
	t_token *tokens;
	int error;
	using_history();
	while (1)
	{
		input = readline(">>> ");
		if (!input)
			return (0);
		else if (*input)
		{
			add_history(input);
			tokens = malloc(sizeof(t_token));
			if (!tokens)
				return (1);
			error = ft_split_input(tokens, input);
			if (error == 0)
				error = ft_type_input(tokens);
		}
		free(input);
		//debuger na tokeny
		if (error == 0)
		{
			//egzekucja
			//printf("klasa\n");
			for (t_token *p = tokens; p; p = p->next) {
				printf("node: %s\n", p->elem ? p->elem : "(null)");
				printf("type: %s\n", ft_dupa(p->type) ? ft_dupa(p->type) : "7");
			}
		}
        
	}
	rl_clear_history(); //czyścimy historie z >>> - nie wiem czy potrzebne
	return (0);
}
