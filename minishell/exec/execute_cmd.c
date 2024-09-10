/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:57 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 21:17:14 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Check if the standard input and output file descriptor is
 * not STDIN_FILENO or STDOUT_FILENO. If it
 * is, do nothing. If it is not,
	duplicate the file descriptor to STDIN_FILENO or STDOUT_FILENO
 * and if that fails, print an error message, close the input file descriptor,
 *Check if the command string is empty. If it is, print an error message,
 */

void	check_std_in_out_and_empty_comd(t_cammand *cmd, int in_fd, int out_fd)
{
	if (cmd->args[0] == NULL)
	{
		print_error("minishell: ", "", "syntax error empty command\n");
		exit(EXIT_FAILURE);
	}
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(in_fd);
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(out_fd);
			exit(EXIT_FAILURE);
		}
		close(out_fd);
	}
}

/*
	* check if is buildin when i have pipe
	* Check if the command is a path or a relative path
	* If it is, check if the command is executable
	* If it is, execute it
	* If not, print an error message and exit
	note : the frist builtin run in parent
		but if i have pipe and should have buildin run in child
*/
void	free_array(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	execute_cmd(t_cammand *cmd, char **arry_env, t_env *my_en)
{
	char	*full_path;
	int		j;

	j = empty(cmd->args);
	if (j == -1)
	{
		free_array(&arry_env);
		exit(0);
	}
	full_path = find_executable(my_en, cmd->args[j]);
	if (!full_path)
	{
		free_array(&arry_env);
		print_error(cmd->args[j], ": ", "command not found");
		exit(127);
	}
	if (execve(full_path, cmd->args + j, arry_env) == -1)
	{
		perror("execve");
		free(full_path);
		free_array(&arry_env);
		exit(EXIT_FAILURE);
	}
	free(full_path);
	free_array(&arry_env);
}

/*
 * execute a single command
 * check if the command is a builtin
 * check if the command is a relative path or absolute path
 * if it is, execute it
 * if not, print an error message and exit
 */

void	execute_command(t_globale *gbl, int in_fd, int out_fd)
{
	char	**arry_env;

	arry_env = NULL;
	check_std_in_out_and_empty_comd(gbl->commands, in_fd, out_fd);
	arry_env = convert_env_to_array(gbl->my_en);
	if (arry_env == NULL)
		return ;
	execute_relative_path_or_builtins(gbl->commands, arry_env, &gbl->my_en);
	execute_cmd(gbl->commands, arry_env, gbl->my_en);
	free_array(&arry_env);
}

/*
	*The execute_pipeline function is the main function of the pipes operation.
	*It is responsible for creating the pipes,
		forking the processes and executing the commands.
	*The function takes a pointer to a t_globale struct as an argument.
	*The t_globale struct contains information about the global state
		of the program.
	*The function first calls the init_pipe_check_build
		function to initialize the pipes
	and check if any of the commands are builtins.
	*Then it enters a loop that continues until
		there are no more commands to execute.
	*In each iteration of the loop,
		the function forks a new process and executes the current command.
	*The function then moves to the next command in the pipeline
		and closes the unused pipe.
	*After the loop,
		the function waits for all the child processes to finish executing.

	rest of fonction creat_pipe_line(), launch_cmd()
		are in buildins.c couse a norme
*/
int	execute_pipeline(t_globale *gbl)
{
	int	**pipes;
	int	i;

	creat_pipe_line(gbl, &pipes);
	launch_cmd(gbl, pipes);
	i = -1;
	while (++i < gbl->n_pipe)
		free(pipes[i]);
	free(pipes);
	return (g_exit_status);
}
