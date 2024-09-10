/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_commend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 23:52:48 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 23:55:30 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (1);
	if (ft_isalpha(name[0]) == 0 && name[0] != '_')
		return (1);
	i = 1;
	while (name[i] != '\0')
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_name(char *variable)
{
	char	*equals;
	size_t	len;
	char	*name;

	equals = strchr(variable, '=');
	if (!equals)
		return (ft_strdup(variable));
	len = equals - variable;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	strncpy(name, variable, len);
	name[len] = '\0';
	return (name);
}

t_env	*init_env_node(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (value == NULL)
		env->status = 1;
	else
		env->status = 0;
	env->env_name = ft_strdup(name);
	if (value == NULL)
		env->env_data = NULL;
	else
		env->env_data = ft_strdup(value);
	env->next = NULL;
	env->full = NULL;
	return (env);
}

char	*get_value(char *variable)
{
	char	*equals;

	equals = strchr(variable, '=');
	if (!equals)
		return (NULL);
	return (ft_strdup(equals + 1));
}

t_env	*export(char **variable, t_env **env)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (variable[i] == NULL)
	{
		print_env_sorted(*env);
		return (*env);
	}
	while (variable[i] != NULL)
	{
		name = get_name(variable[i]);
		value = get_value(variable[i]);
		if (is_valid_name(name) != 0)
			g_exit_status = 1;
		add_or_update_env(env, name, value);
		if (name)
			free(name);
		if (value)
			free(value);
		i++;
	}
	return (*env);
}
