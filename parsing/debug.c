// #include "../minishell.h"

// static void print_str_array(char **arr, const char *name)
// {
//     int i = 0;

//     if (!arr)
//     {
//         printf("%s: (null)\n", name);
//         return;
//     }
//     printf("%s:\n", name);
//     while (arr[i])
//     {
//         printf("  [%d] \"%s\"\n", i, arr[i]);
//         i++;
//     }
// }

// void print_command_list(t_command *cmd)
// {
//     int index = 0;

//     if (!cmd)
//     {
//         printf("Command list is empty.\n");
//         return;
//     }

//     while (cmd)
//     {
//         printf("\n========== COMMAND %d ==========\n", index);
//         print_str_array(cmd->arg, "ARGS");
//         print_str_array(cmd->red_in, "REDIRECT IN");
//         print_str_array(cmd->red_out, "REDIRECT OUT");
//         print_str_array(cmd->heredoc, "HEREDOC");

//         printf("append:        %s\n", cmd->append ? "true" : "false");
//         printf("b_heredoc:     %s\n", cmd->b_heredoc ? "true" : "false");
//         printf("heredoc_count: %d\n", cmd->heredoc_count);
//         printf("=================================\n");

//         cmd = cmd->next;
//         index++;
//     }
// }