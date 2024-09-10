/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:42 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 00:16:12 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*my_env(char **env)
{
	int		i;
	t_env	*heder;

	i = 0;
	if (env == NULL)
		return (NULL);
	heder = NULL;
	while (env[i] != NULL)
	{
		if (heder == NULL)
			heder = creat_env(env[i], NULL);
		else
			creat_env(env[i], heder);
		i++;
	}
	return (heder);
}

static char	*find_env_value(char *var_name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->env_name, var_name, ft_strlen(env->env_name)
				+ 1) == 0)
		{
			return (env->env_data);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*find_direct_path(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->env_name, name, ft_strlen(env->env_name) + 1) == 0)
		{
			return (ft_strdup(env->env_data));
		}
		env = env->next;
	}
	return (NULL);
}

static char	*find_variable_path(char *name, t_env *env)
{
	char	*var_name;
	char	*path;
	char	*slash_pos;

	var_name = get_name_of_var(name + 1);
	path = find_env_value(var_name, env);
	free(var_name);
	if (path == NULL)
		return (NULL);
	slash_pos = ft_strchr(name + 1, '/');
	if (slash_pos != NULL)
		return (ft_strjoin(path, slash_pos));
	return (ft_strdup(path));
}

char	*find_path(char *name, t_env *env)
{
	if (name[0] == '$')
	{
		return (find_variable_path(name, env));
	}
	return (find_direct_path(name, env));
}
