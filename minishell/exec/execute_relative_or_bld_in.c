/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_relative_or_bld_in.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:46:42 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/04 20:46:43 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtins(t_cammand *cmd, t_env **my_en, char **arry_env)
{
	if (builtins(cmd->args, my_en) == 0)
	{
		free_array(&arry_env);
		exit(EXIT_SUCCESS);
	}
}

void	execute_path_command(t_cammand *cmd, char **arry_env)
{
	if (cmd->args[0][0] == '/' || (cmd->args[0][0] == '.'
			&& cmd->args[0][1] == '/'))
	{
		if (access(cmd->args[0], F_OK) != 0)
		{
			print_error(cmd->args[0], ": ", "No such file or directory");
			free_array(&arry_env);
			exit(127);
		}
		else if (access(cmd->args[0], X_OK) != 0)
		{
			print_error(cmd->args[0], ": ", "Permission denied");
			free_array(&arry_env);
			exit(126);
		}
		else
		{
			execve(cmd->args[0], cmd->args, arry_env);
			perror("execve");
			free_array(&arry_env);
			exit(126);
		}
	}
}

void	execute_relative_path_or_builtins(t_cammand *cmd, char **arry_env,
		t_env **my_en)
{
	execute_builtins(cmd, my_en, arry_env);
	execute_path_command(cmd, arry_env);
}
