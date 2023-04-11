

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

typedef struct s_io_data
{
	char	*infile;
	char	*outfile;
	char	*heredoc_del;
	int		in_fd;
	int		out_fd;
}	t_io_data;

typedef struct s_command
{
	char				*str;
	char				**args;
	int					pipe_fd[2];
	int					pipe;
	t_io_data			io_data;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char		*line;
	int			status;
	char		**env;
	t_token		*tokens;
	t_command	*commands;
}	t_data;

enum	e_token {
	WORD,
	PIPE,
	INPUT,
	HEREDOC,
	TRUNC,
	APPEND,
	END
};

enum	e_quote {
	DEFAULT,
	SQUOTE,
	DQUOTE
};

int		lexer(t_data *data);
t_token	*create_token(char *str, int type);
void	add_token(t_token **tokens, t_token *new);
t_token	*get_last_token(t_token **tokens);

char	*ft_strndup(const char *s1, int len);
int		is_space(char c);
int		is_operator(char *line);
int		set_quote_status(int status, char c);

void	error_msg(char *msg, char *token, int quoting);

void    free_tokens(t_token *tokens);
void    free_data(t_data *data);
void	free_str_array(char **strs);

#endif
