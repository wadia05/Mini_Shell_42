/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sort_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:45:45 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/04 20:45:46 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_sort(t_env **array, int count)
{
	t_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if ((array[j]->env_name[0] >= 65 && array[j]->env_name[0] <= 122)
				&& (array[j + 1]->env_name[0] >= 65 && array[j
						+ 1]->env_name[0] <= 122) && ft_strncmp(
					array[j]->env_name,
					array[j + 1]->env_name, ft_strlen(array[j + 1]->env_name)
					+ 1) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

t_env	**create_env_array(t_env *env, int count)
{
	int		i;
	t_env	**env_array;
	t_env	*tmp;

	i = 0;
	env_array = malloc(count * sizeof(t_env *));
	if (!env_array)
	{
		perror("malloc");
		return (NULL);
	}
	tmp = env;
	while (i < count)
	{
		env_array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	return (env_array);
}

int	count_env_variables(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	print_sorted_env(t_env **env_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (env_array[i]->status == 0)
			printf("declare -x %s=\"%s\"\n", env_array[i]->env_name,
				env_array[i]->env_data);
		else
			printf("declare -x %s=''\n", env_array[i]->env_name);
		i++;
	}
}

int	print_env_sorted(t_env *env)
{
	int		count;
	t_env	**env_array;

	count = count_env_variables(env);
	env_array = create_env_array(env, count);
	if (!env_array)
		return (1);
	env_sort(env_array, count);
	print_sorted_env(env_array, count);
	free(env_array);
	return (0);
}
