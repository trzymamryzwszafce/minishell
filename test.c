#include "minishell.h"

void split_input(t_mini arguments, char *input)
{
	int i;
	char **splited_input;

	i = 0;
	splited_input = ft_split(input, ' ');
	while (splited_input[i])
	{
		arguments.arg_list = splited_input[i];
		printf("%s$\n", arguments.arg_list); //żeby zobaczyć czy na pewno dobrze jest
		i++;
	}
}

int main(void)
{
	t_mini arguments;
	char *input;

	using_history(); //historia tego co było wcześniej wpisywane w >>>

	while (1) {
		input = readline(">>> ");
		if (!input)
			return (0);
		else if (*input)
		{
			add_history(input); //dodajemy historię
			split_input(arguments, input);
			//printf("You typed: %s\n", input);
		}
		free(input);
	}
	rl_clear_history(); //czyścimy historie z >>>
	return (0);
}

