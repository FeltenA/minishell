
#include "minishell.h"

int	free_return(void *p)
{
	if (p)
		free(p);
	p = 0;
	return (0);
}

int	ft_strs_len(char **strs)
{
	int		i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int	is_env_var(char *str)
{
	if (str[0] == '$' && (ft_isalpha(str[1]) || str[1] == '_'
			|| str[1] == '?'))
		return (1);
	return (0);
}
