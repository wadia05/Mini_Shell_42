/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_commed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:49 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/03 23:57:38 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_matching_env(t_env *env, char *name, int len)
{
	return (ft_strncmp(env->env_name, name, len + 1) == 0
		&& env->env_name[len] == '\0');
}

static void	free_env_node(t_env *node, int status)
{
	if (status == 0)
	{
		free(node->env_data);
		free(node->full);
	}
	free(node->env_name);
	node->env_data = NULL;
	node->env_name = NULL;
	node->full = NULL;
	free(node);
	node = NULL;
}

static void	remove_matching_nodes(t_env **env, char *name, int len)
{
	t_env	*prev;
	t_env	*current;

	prev = (*env);
	current = (*env)->next;
	if (!ft_strncmp((*env)->env_name, name, ft_strlen(name) + 1))
	{
		free_env_node(prev, prev->status);
		(*env) = current;
		return ;
	}
	while (current != NULL)
	{
		if (is_matching_env(current, name, len))
		{
			prev->next = current->next;
			free_env_node(current, current->status);
			current = prev->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

static t_env	*remove_env_variable(char *name, t_env **env)
{
	int	len;

	if (name == NULL)
		return (NULL);
	len = ft_strlen(name);
	if (*env)
	{
		remove_matching_nodes(env, name, len);
	}
	return (*env);
}

t_env	*my_unset(char **name, t_env **env)
{
	int	i;

	i = 0;
	while (name[++i] != NULL)
		remove_env_variable(name[i], env);
	return (*env);
}
