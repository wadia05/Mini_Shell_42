/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_2_arry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:46:39 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/04 20:46:40 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current != NULL)
	{
		if (current->status == 0)
			count++;
		current = current->next;
	}
	return (count);
}

static char	**allocate_env_array(int count)
{
	char	**env_array;

	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	return (env_array);
}

static int	fill_env_array(char **env_array, t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current != NULL)
	{
		if (current->status == 0)
		{
			env_array[i] = ft_strdup(current->full);
			if (!env_array[i])
			{
				while (i > 0)
				{
					free(env_array[--i]);
				}
				free(env_array);
				return (0);
			}
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**convert_env_to_array(t_env *env)
{
	int		count;
	char	**env_array;

	count = count_env_vars(env);
	env_array = allocate_env_array(count);
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, env))
		return (NULL);
	return (env_array);
}
