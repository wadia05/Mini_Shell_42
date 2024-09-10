/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:08:01 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 21:21:42 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_data_(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (strncmp(env->env_name, name, strlen(env->env_name) + 1) == 0)
			break ;
		env = env->next;
	}
	if (env != NULL && env->env_data != NULL)
		return (ft_split(env->env_data, ':'));
	return (NULL);
}

char	*test_access_path(char **full_path, char *cmd)
{
	char	*executable;
	int		i;
	char	*test_path;
	char	*complete_path;

	executable = NULL;
	i = 0;
	while (full_path[i] != NULL)
	{
		test_path = ft_strjoin(full_path[i], "/");
		complete_path = ft_strjoin(test_path, cmd);
		free(test_path);
		if (access(complete_path, X_OK) == 0)
		{
			executable = ft_strdup(complete_path);
			free(complete_path);
			break ;
		}
		free(complete_path);
		i++;
	}
	return (executable);
}

char	*find_executable(t_env *my_en, char *cmd)
{
	char	**full_path;
	char	*executable;
	int		j;

	j = -1;
	full_path = get_data_(my_en, "PATH");
	executable = NULL;
	if (full_path)
	{
		executable = test_access_path(full_path, cmd);
		while (full_path[++j] != NULL)
			free(full_path[j]);
		free(full_path);
	}
	return (executable);
}

int	cont_pipe(t_cammand *cmd)
{
	int	cont;

	cont = 0;
	while (cmd != NULL)
	{
		if (cmd->type == T_PIPE)
			cont++;
		cmd = cmd->next;
	}
	return (cont);
}
