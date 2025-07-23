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

int main(void)
{
	t_mini *arguments;
	char *input;

	using_history();
	while (1) {
		input = readline(">>> ");
		if (!input)
			return (0);
		else if (*input)
		{
			add_history(input);
			arguments = malloc(sizeof(t_mini));
			if (!arguments)
				return (1);
			ft_split_input(arguments, input);
		}
		free(input);
		ft_lexer(arguments);
		
		// //debuger dla lexera
		// t_lexer *cur = arguments->lexer;
		// int node = 1;
		// while (cur)
		// {
		// 	printf("\n--- NODE %d ---\n", node++);
		// 	printf("command : %s\n", cur->command ? cur->command : "(null)");
		// 	printf("flag    : %s\n", cur->flag ? cur->flag : "(null)");
		// 	if (cur->params)
		// 	{
		// 		printf("arguments:\n");
		// 		for (int i = 0; cur->params[i]; i++)
		// 			printf("  [%d] %s\n", i, cur->params[i]);
		// 	}
		// 	else
		// 		printf("arguments: (null)\n");
		// 	if (cur->type && cur->redir_targets)
		// 	{
		// 		printf("redirections:\n");
		// 		for (int i = 0; cur->type[i] && cur->redir_targets[i]; i++)
		// 			printf("  %s -> %s\n", cur->type[i], cur->redir_targets[i]);
		// 	}
		// 	else
		// 		printf("redirections: (none)\n");
		// 	cur = cur->next;
		// }
		
		ft_free_mini(arguments);
	}
	rl_clear_history(); //czyścimy historie z >>> - nie wiem czy potrzebne
	return (0);
}

