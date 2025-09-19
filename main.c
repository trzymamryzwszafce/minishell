#include "minishell.h"

void ft_free_mini(t_mini *arguments)
{
	t_lexer *tmp;
	ft_free_split(arguments->arg_list);
	while (arguments->lexer)
	{
		tmp = arguments->lexer->next;
		free(arguments->lexer->command);
		free(arguments->lexer->flag);
		if (arguments->lexer->params)
			ft_free_split(arguments->lexer->params);
		if (arguments->lexer->type)
			ft_free_split(arguments->lexer->type);
		if (arguments->lexer->redir_targets)
			ft_free_split(arguments->lexer->redir_targets);
		free(arguments->lexer);
		arguments->lexer = tmp;
	}
	free(arguments);
}

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
		case REDIR_FILE_OUT : return "file aft out redir";
		case REDIR_FILE_IN : return "file aft in redir";
		case ENV : return "env";
	}
	return (NULL);
}

int main(void)
{
//	t_mini *arguments;
	char *input;
	t_token *tokens;
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
			ft_split_input(tokens, input);
			ft_tokenizer_input(tokens);
		}
		free(input);
		//debuger na tokeny
		for (t_token *p = tokens; p; p = p->next) {
			printf("node: %s\n", p->elem ? p->elem : "(null)");
			printf("type: %s\n", ft_dupa(p->type) ? ft_dupa(p->type) : "7");
		}

		//	ft_free_mini(arguments);
	}
	rl_clear_history(); //czyścimy historie z >>> - nie wiem czy potrzebne
	return (0);
}

