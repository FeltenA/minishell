

#include "minishell.h"

t_token	*create_token(char *str, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->str = str;
	new->type = type;
	new->next = 0;
	new->prev = 0;
	return (new);
}

t_token	*get_last_token(t_token **tokens)
{
	t_token	*first;

	if (!tokens)
		return (0);
	first = *tokens;
	while (first && first->next)
		first = first->next;
	return (first);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*temp;

	temp = get_last_token(tokens);
	if (!temp)
		*tokens = new;
	else
	{
		temp->next = new;
		new->prev = temp;
	}
}
