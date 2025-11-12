#include "../minishell.h"

void ft_count_struct(t_token *tokens, t_data *data)
{
    t_token *cur;
    int count_cmds;
    int count_heredoc;

    cur = tokens;
    if (!tokens)
        return  ;
    count_cmds = 0;
    count_heredoc = 0;
    while (cur != NULL)
    {
        if (cur->type == PIPE)
            count_cmds++;
        else if (cur->type == R_HEREDOC)
            count_heredoc++;    
        cur = cur->next;
    }
    data->cmd_count = count_cmds + 1;
    data->cmd->heredoc_count = count_heredoc;
}

// void ft_find_heredoc(t_token *tokens, t_command *cmd)
// {
//     while ()
// }

void ft_struct_filler(t_token *tokens, t_envp **envp, t_data *data)
{   
    ft_count_struct(tokens, data);
    //ft_find_heredoc(tokens, data);
}