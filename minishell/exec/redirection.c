/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:25 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 23:40:37 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	set-up redirection for input and output
*/
int	set_redirection_input(t_cammand *cmd, t_globale *gbl)
{
	if (cmd->type == T_LESS)
	{
		gbl->in_fd = open(cmd->args[1], O_RDONLY);
		if (gbl->in_fd == -1)
		{
			print_error("minishell: ", cmd->args[1],
				"No such file or directory\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd->type == T_DLESS)
	{
		gbl->in_fd = open(cmd->input_file, O_RDONLY);
		if (gbl->in_fd == -1)
		{
			perror("Error opening heredoc file for reading");
			exit(EXIT_FAILURE);
		}
	}
	else
		return (1);
	return (0);
}

int	set_redirection_output(t_cammand *cmd, t_globale *gbl)
{
	if (cmd->type == T_DGREAT)
	{
		gbl->out_fd = open(cmd->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (gbl->out_fd == -1)
		{
			perror("open output file (append)");
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd->type == T_GREAT)
	{
		gbl->out_fd = open(cmd->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (gbl->out_fd == -1)
		{
			perror("open output file");
			exit(EXIT_FAILURE);
		}
	}
	else
		return (1);
	return (0);
}

/*
	apply redirection for input and output
	frist check if there is heredoc
	then check if there is redirection
	then apply redirection by dup2 and close files duplicate
*/
void	apply_redirection(t_cammand *cmd, t_globale *gbl)
{
	while (cmd && cmd->type != T_PIPE)
	{
		if (set_redirection_input(cmd, gbl) == 1)
			set_redirection_output(cmd, gbl);
		cmd = cmd->next;
	}
	if (gbl->in_fd != STDIN_FILENO)
	{
		if (dup2(gbl->in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close(gbl->in_fd);
	}
	if (gbl->out_fd != STDOUT_FILENO)
	{
		dup2(gbl->out_fd, STDOUT_FILENO);
		close(gbl->out_fd);
	}
}
