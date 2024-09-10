/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:45:37 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 00:12:22 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_node(char *name, char *value)
{
	t_env	*env;
	char	*tmp;

	env = init_env_node(name, value);
	if (!env || !env->env_name || (value && !env->env_data))
	{
		if (env)
		{
			free(env->env_name);
			free(env->env_data);
			free(env);
		}
		return (NULL);
	}
	if (value)
	{
		tmp = ft_strjoin(name, "=");
		if (tmp)
		{
			env->full = ft_strjoin(tmp, value);
			free(tmp);
		}
	}
	return (env);
}

void	update_existing_env(t_env *current, char *value)
{
	if (value == NULL)
		return ;
	if (current->env_data == NULL)
		current->status = 0;
	free(current->env_data);
	current->env_data = ft_strdup(value);
}

void	add_or_update_env(t_env **env, char *name, char *value)
{
	t_env	*current;
	t_env	*prev;
	t_env	*new;

	current = *env;
	prev = NULL;
	if (*env == NULL)
	{
		*env = create_env_node(name, value);
		return ;
	}
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, name, ft_strlen(name) + 1) == 0)
		{
			update_existing_env(current, value);
			return ;
		}
		prev = current;
		current = current->next;
	}
	new = create_env_node(name, value);
	if (new)
		prev->next = new;
}
