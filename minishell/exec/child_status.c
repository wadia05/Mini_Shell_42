/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:46:37 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/04 20:46:38 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_child_status(int status)
{
	int	exit_status;

	exit_status = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit_status = 130;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			exit_status = 131;
		}
	}
	else if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
	}
	return (exit_status);
}
