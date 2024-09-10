/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:23 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 22:04:29 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_heredocs(t_cammand *cmd, t_env *env)
{
	t_cammand	*curr;

	curr = cmd;
	while (curr != NULL)
	{
		if (curr->type == T_DLESS)
		{
			process_heredoc(curr->args[1], env, curr->input_file);
		}
		curr = curr->next;
	}
}

static int	fork_child_process(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	handle_child_process(t_cammand *cmd, t_env *env)
{
	setup_heredoc_child_signals();
	process_heredocs(cmd, env);
	exit(EXIT_SUCCESS);
}

void	process_all_heredocs(t_cammand *cmd, t_env *env)
{
	int	pid;

	pid = fork_child_process();
	if (pid == 0)
		handle_child_process(cmd, env);
	else
		handle_parent_process(pid);
}
