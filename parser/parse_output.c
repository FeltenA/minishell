

#include "minishell.h"

void	free_output(t_command *command)
{
	if (command->io_data.outfile)
		free(command->io_data.outfile);
	if (command->io_data.out_fd != -1)
		close(command->io_data.out_fd);
	command->io_data.outfile = 0;
	command->io_data.out_fd = -1;
}

int	parse_trunc(t_command *command, t_token **token)
{
	if (!command->io_data.outfile)
		free_output(command);
	command->outfile = 
}