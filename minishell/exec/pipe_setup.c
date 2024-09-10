/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:29 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 21:59:26 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_pipe(t_globale *gbl, int i, int **pipes)
{
	int	j;

	j = -1;
	if (i > 0)
		gbl->in_fd = pipes[i - 1][0];
	if (i < gbl->n_pipe)
		gbl->out_fd = pipes[i][1];
	while (++j < gbl->n_pipe)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
	}
}

t_cammand	*move_to_next_command(t_globale *gbl, int i, int **pipes)
{
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < gbl->n_pipe)
		close(pipes[i][1]);
	while (gbl->commands && gbl->commands->type != T_PIPE)
		gbl->commands = gbl->commands->next;
	if (gbl->commands && gbl->commands->type == T_PIPE)
		gbl->commands = gbl->commands->next;
	return (gbl->commands);
}

int	wait_for_parnt_babys(t_globale *gbl)
{
	int	i;
	int	status;
	int	exit_status;

	status = 0;
	exit_status = 0;
	i = -1;
	while (++i < gbl->n_pipe + 1)
	{
		temporarily_ignore_signals();
		waitpid(-1, &status, 0);
		exit_status = handle_child_status(status);
	}
	g_exit_status = exit_status;
	restore_signal_handlers();
	return (g_exit_status);
}

void	*init_pipe_check_build(t_globale *gbl, int **pipes)
{
	int	i;

	i = -1;
	if (gbl->n_pipe == 0 && gbl->commands->type == T_COMMEND)
	{
		if (builtins(gbl->commands->args, &gbl->my_en) == 0)
			return (NULL);
	}
	while (++i < gbl->n_pipe)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	return ("a");
}

void	i_am_the_baby(t_globale *gbl, int i, int **pipes)
{
	if (gbl->pid == 0)
	{
		setup_child_signals();
		setup_pipe(gbl, i, pipes);
		apply_redirection(gbl->commands, gbl);
		while (gbl->commands && gbl->commands->type != T_COMMEND
			&& gbl->commands->type != T_PIPE)
			gbl->commands = gbl->commands->next;
		execute_command(gbl, STDIN_FILENO, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}
