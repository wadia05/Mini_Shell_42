/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:08:05 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 21:51:58 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// rest of your code
/*
 * The builtins function is a function that checks if the command passed
 * as an argument is a builtin command (echo, pwd, cd, env, export, unset).
 * If it is, the function executes the command and returns 0.
 * If it isn't, the function returns 1.
 * The function takes two arguments:
 *	- command: a pointer to a string array that contains
  the command to be executed.
 *	- env: a pointer to a t_env struct that contains
 information about the environment.
 */
int	builtins(char **command, t_env **env)
{
	int	j;

	j = empty(command);
	if (j == -1)
	{
		g_exit_status = 0;
		return (2);
	}
	if (ft_strncmp(command[j], "echo", 5) == 0)
		my_echo(command + j);
	else if (ft_strncmp(command[j], "pwd", 4) == 0)
		my_pwd();
	else if (ft_strncmp(command[j], "cd", 3) == 0)
		my_cd(command + j, *env);
	else if (ft_strncmp(command[j], "env", 4) == 0)
		envarment(*env);
	else if (ft_strncmp(command[j], "export", 7) == 0)
		export(command + j, env);
	else if (ft_strncmp(command[j], "unset", 7) == 0)
		my_unset(command + j, env);
	else if (strncmp(command[j], "exit", 5) == 0)
		my_exit(command + j);
	else
		return (1);
	return (0);
}

/*
 * The creat_pipe_line function is a function that creates the pipes necessary
 * for the execution of the commands.
 * The function takes one argument:
 *	- gbl: a pointer to a t_globale struct that contains
 information about the global state
 *		of the program.
 * The function allocates memory for the pipes and initializes them.
 */

void	creat_pipe_line(t_globale *gbl, int ***pipes)
{
	int	i;

	gbl->n_pipe = cont_pipe(gbl->commands);
	*pipes = malloc(gbl->n_pipe * sizeof(int *));
	if (!*pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < gbl->n_pipe)
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!(*pipes)[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
}

// /*
//  * The launch_cmd function is a function that executes
//  the commands passed as arguments.
//  * The function takes two arguments:
//  *	- gbl: a pointer to a t_globale struct that contains
//  information about the global state
//  *		of the program.
//  *	- pipes: a pointer to a pointer to an integer
//   array that contains the pipes necessary
//  *		for the execution of the commands.
//
//	* The function forks a new process for
// each command and executes the commands.
//  * The function waits for all the child
// processes to finish executing.
//  */

void	extract_heredoc_names(t_cammand *cmd)
{
	char		*num;
	char		*name;
	t_cammand	*tmp;
	int			i;

	num = NULL;
	name = NULL;
	tmp = cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->type == T_DLESS)
		{
			num = ft_itoa(++i);
			name = ft_strjoin(TMP_FD, num);
			tmp->input_file = ft_strdup(name);
			free(name);
			free(num);
		}
		tmp = tmp->next;
	}
}

void	launch_cmd(t_globale *gbl, int **pipes)
{
	int			i;
	t_cammand	*here;

	if ((char *)init_pipe_check_build(gbl, pipes) == NULL)
		return ;
	i = 0;
	here = gbl->commands;
	extract_heredoc_names(here);
	process_all_heredocs(gbl->commands, gbl->my_en);
	while (gbl->commands)
	{
		gbl->pid = fork();
		if (gbl->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		i_am_the_baby(gbl, i, pipes);
		gbl->commands = move_to_next_command(gbl, i, pipes);
		i++;
	}
	g_exit_status = wait_for_parnt_babys(gbl);
}
