
#include "minishell.h"

void	execute_command(t_data *data, t_command *command)
{
	data->status = 1;
	close_pipes(data->commands, command);
	if (!redirect_io(command, data))
		exit_shell(data);
	if (is_builtin(command->str))
	{
		data->status = execute_builtin(data, command);
		exit_shell(data);
	}
	if (!execute_env_cmd(data, command))
		exit_shell(data);
	execute_local_cmd(data, command);
	exit_shell(data);
}

static int	wait_children(t_data *data)
{
	pid_t	pid;
	int		status;

	close_pipes(data->commands, 0);
	pid = 0;
	status = data->status;
	while (pid != -1 || errno != ECHILD)
		pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	return (status);
}

int	exec_first_builtin(t_command **cmd, t_data *data)
{
	int	save_out;
	int	save_in;

	save_in = -1;
	save_out = -1;
	if ((*cmd)->io_data.in_fd != -1)
		save_in = dup(0);
	if ((*cmd)->io_data.out_fd != -1 || (*cmd)->pipe_fd[1] != -1)
		save_out = dup(1);
	if (!redirect_io(*cmd, data))
		return (0);
	data->status = execute_builtin(data, *cmd);
	if (save_in != -1)
		dup2(save_in, 0);
	if (save_out != -1)
		dup2(save_out, 1);
	if (data->status != 0)
		return (0);
	*cmd = (*cmd)->next;
	return (1);
}

int	execution(t_data *data)
{
	t_command	*commands;
	pid_t		pid;

	if (!create_pipes(data->commands, data))
		return (0);
	commands = data->commands;
	if (is_builtin(commands->str) && !exec_first_builtin(&commands, data))
		return (0);
	while (commands)
	{
		if (!commands->str)
		{
			commands = commands->next;
			continue ;
		}
		pid = fork();
		if (pid == -1)
			return (perror_return(data, "fork: "));
		else if (pid == 0)
			execute_command(data, commands);
		commands = commands->next;
	}
	data->status = wait_children(data);
	return (1);
}
