#include "../minishell.h"

static void init_cmd(t_command *cmd)
{
    cmd->arg = NULL;
    cmd->red_in = NULL;
    cmd->red_out = NULL;

    cmd->append = false;

    cmd->heredoc = NULL;
    cmd->b_heredoc = false;
    cmd->heredoc_count = 0;

    cmd->next = NULL;
}

void count_and_alloc_for_cmd(t_token *start, t_command *cmd)
{
    t_token *cur;
    int args;
    int rin;
    int rout;

    cur = start;
    args = 0;
    rin = 0;
    rout = 0;

    while (cur->next != NULL && cur->type != PIPE)
    {
        if (cur->type == ARG)
            args++;
        else if (cur->type == ARG_IN)
            rin++;
        else if (cur->type == ARG_OUT)
            rout++;
        cur = cur->next;
    }
    cmd->arg = calloc(args + 1, sizeof(char *));
    cmd->red_in = calloc(rin + 1, sizeof(char *));
    cmd->red_out = calloc(rout + 1, sizeof(char *));
}


static t_token *fill_one_cmd(t_token *start, t_command *cmd)
{
    t_token *cur = start;

    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (cur->next != NULL && cur->type != PIPE)
    {
        if (cur->type == ARG)
            cmd->arg[i++] = strdup(cur->elem);
        else if (cur->type == ARG_IN)
            cmd->red_in[j++] = strdup(cur->elem);
        else if (cur->type == ARG_OUT)
            cmd->red_out[k++] = strdup(cur->elem);
        else if (cur->type == R_HEREDOC)
        {
            cmd->b_heredoc = true;
            cmd->heredoc_count++;
        }
        cur = cur->next;
    }
    return (cur); // cur == PIPE or NULL
}

void ft_struct_filler(t_token *tokens, t_envp **envp, t_data *data)
{
    (void)envp;

    t_token     *cur;
    t_command   *cmd;

    cur = tokens;
    data->cmd = malloc(sizeof(t_command));
    init_cmd(data->cmd);
    cmd = data->cmd;

    while (cur->next != NULL)
    {
        count_and_alloc_for_cmd(cur, cmd);
        cur = fill_one_cmd(cur, cmd);
        if (cur && cur->type == PIPE)
        {
            cur = cur->next;

            cmd->next = malloc(sizeof(t_command));
            init_cmd(cmd->next);
            cmd = cmd->next;
        }
    }
}
