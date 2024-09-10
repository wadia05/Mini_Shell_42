/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:11:13 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 03:19:14 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, char size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (*(s1 + i) && (size > i || size == -1))
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char	*get_name_of_var(char *name)
{
	char	*nm;
	int		i;

	nm = NULL;
	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 1)
			i++;
		else if (name[i] == '_')
			i++;
		else
			break ;
	}
	if (name[i] == '\0')
		return (NULL);
	nm = ft_strndup(name, i);
	return (nm);
}

char	*get_data_of_var(char *data)
{
	int		i;
	char	*data_v;

	i = 0;
	while (data[i] != '=')
		i++;
	data_v = ft_strndup(&data[++i], -1);
	return (data_v);
}

t_env	*creat_env(char *env, t_env *add_to_list)
{
	t_env	*env_v;
	t_env	*last;

	env_v = malloc(sizeof(t_env));
	if (env_v == NULL)
		return (NULL);
	env_v->full = ft_strndup(env, -1);
	env_v->status = 0;
	env_v->env_name = get_name_of_var(env);
	env_v->env_data = get_data_of_var(env);
	env_v->next = NULL;
	if (add_to_list == NULL)
		return (env_v);
	last = add_to_list;
	while (last->next != NULL)
		last = last->next;
	last->next = env_v;
	return (add_to_list);
}
