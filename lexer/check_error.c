

#include "minishell.h"

t_token	*get_last_token(t_token **tokens);

int	check_syntax(t_data *data, int end)
{
	t_token	*token;

	token = get_last_token(&data->tokens);
	if (token)
	{
		if ((token->type >= PIPE && token->type != END
				&& token->prev && token->prev->type >= PIPE)
			|| (token->type == PIPE && !token->prev))
		{
			error_msg("syntax error near unexpected token", token->str, 1);
			return (1);
		}
		if (end)
		{
			if (token->type > PIPE && token->type != END)
				error_msg("syntax error near unexpected token", "newline", 1);
			else if (token->type == PIPE)
				error_msg("syntax error", "unexpected end of file", 0);
			return (1);
		}
	}
	return (0);
}
