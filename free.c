

#include "minishell.h"

void    free_tokens(t_token *tokens)
{
    t_token *temp;

    while (tokens)
    {
        temp = tokens->next;
        free(tokens->str);
        free(tokens);
        tokens = temp;
    }
}

void    free_data(t_data *data)
{
    if (data->line)
        free(data->line);
    if (data->tokens)
        free_tokens(data->tokens);
    data->line = 0;
    data->tokens = 0;
}

void	free_str_array(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}