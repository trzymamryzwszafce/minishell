#include "minishell.h"

int main(void)
{
	t_mini *arguments;
	char *input;

	using_history(); //historia tego co było wcześniej wpisywane w >>>

	while (1) {
		input = readline(">>> ");
		if (!input)
			return (0);
		else if (*input)
		{
			add_history(input); //dodajemy historię
			arguments = malloc(sizeof(t_mini));
			if (!arguments)
				return (1);
			ft_split_input(arguments, input);
		}
		free(input);
		//debug
		// //printf("%d\n", count_2d_array(arguments->arg_list));
		// int j = 0;
		// while (arguments->arg_list[j])
		// {
		// 	printf("%s$\n", arguments->arg_list[j]);
		// 	j++;
		// }
		ft_lexer(arguments);
		t_lexer *cur = arguments->lexer;
		while (cur)
		{
			printf("cmd: %s || flag: %s || arg: %s || type: %s\n",
				cur->command, cur->flag, cur->argument, cur->type);
			cur = cur->next;
		}
	}
	
	//zwolnienie pamięci tylko arguments
	int i = 0;
	while (arguments->arg_list[i])
		free(arguments->arg_list[i++]);
	free(arguments->arg_list);
	free(arguments);
	rl_clear_history(); //czyścimy historie z >>> - nie wiem czy potrzebne
	return (0);
}

