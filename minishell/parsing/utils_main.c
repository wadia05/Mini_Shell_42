/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:26:27 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/05 02:20:36 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	signal(sig, SIG_IGN);
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

t_cammand	*finalize_current_command(t_cammand **current_cmd,
		t_cammand **head_cmd, t_cammand **final_cmd, int *idx)
{
	if (*final_cmd && *idx > 0)
	{
		(*final_cmd)->args[*idx] = NULL;
		if (*current_cmd)
		{
			(*current_cmd)->next = *final_cmd;
		}
		else
		{
			*head_cmd = *final_cmd;
		}
		*current_cmd = *final_cmd;
		*final_cmd = NULL;
		*idx = 0;
	}
	return (*current_cmd);
}

t_token	*allocate_new_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	return (new_token);
}
