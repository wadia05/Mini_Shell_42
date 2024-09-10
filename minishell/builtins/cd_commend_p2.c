/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_commend_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:07:45 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 02:29:07 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_env *env, char *new_value, char *name)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->env_name, name, ft_strlen(name)) == 0)
		{
			free(temp->env_data);
			free(temp->full);
			temp->full = ft_strdup(new_value);
			temp->env_data = get_data_of_var(new_value);
			return ;
		}
		temp = temp->next;
	}
	if (temp == NULL)
		env = creat_env(new_value, env);
}

// int	handle_too_many_arguments(char **name_dir)
// {
// 	int	i;

// 	i = 0;
// 	while (name_dir[i] != NULL)
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_putstr_fd("bash: cd: too many arguments\n", 2);
// 		g_exit_status = 1;
// 		return (1);
// 	}
// 	return (0);
// }

char	*error_check(char *name, t_env *env, char *error_message)
{
	char	*target_dir;

	target_dir = find_path(name, env);
	if (target_dir == NULL)
	{
		ft_putstr_fd(error_message, 2);
		g_exit_status = 1;
		return (NULL);
	}
	return (target_dir);
}
