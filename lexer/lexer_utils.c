
#include "minishell.h"

char	*ft_strndup(const char *s1, int len)
{
	int		i;
	char	*s2;
    
	s2 = malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

int	is_space(char c)
{
	return (c == ' ' || (c > 7 && c < 14));
}

int	is_operator(char *line)
{
	if (*line == '>' && *(line + 1) == '>')
		return (APPEND);
	else if (*line == '<' && *(line + 1) == '<')
		return (HEREDOC);
	else if (*line == '|')
		return (PIPE);
	else if (*line == '<')
		return (INPUT);
	else if (*line == '>')
		return (TRUNC);
	else if (*line == '\0')
		return (END);
	return (0);
}

int	set_quote_status(int status, char c)
{
	if (status == DEFAULT && c == '\"')
		return (DQUOTE);
	else if (status == DEFAULT && c == '\'')
		return (SQUOTE);
	else if (status == DQUOTE && c == '\"')
		return (DEFAULT);
	else if (status == SQUOTE && c == '\'')
		return (DEFAULT);
	return (status);
}
