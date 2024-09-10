/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 02:20:55 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 04:00:56 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_env *node)
{
	if (node)
	{
		free(node->full);
		free(node->env_name);
		free(node->env_data);
		node->full = NULL;
		node->env_name = NULL;
		node->env_data = NULL;
		free(node);
		node = NULL;
	}
}

void	free_env(t_globale *gbl)
{
	t_env	*current;
	t_env	*next_node;

	current = gbl->my_en;
	while (current != NULL)
	{
		next_node = current->next;
		free_node(current);
		current = next_node;
	}
}

int	empty(char **line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != NULL)
	{
		if (line[i][0] == '\0')
			j++;
		if (line[i][0] != '\0')
			return (j);
		i++;
	}
	return (-1);
}

void	free_commands(t_cammand *cmds)
{
	t_cammand	*tmp;
	int			i;

	while (cmds)
	{
		if (cmds->type == T_DLESS)
			free(cmds->input_file);
		tmp = cmds;
		cmds = cmds->next;
		i = 0;
		while (tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		free(tmp);
	}
}

void	exit_shell(t_globale *gbl)
{
	write(STDOUT_FILENO, "exit\n", 5);
	free_env(gbl); 
	free(gbl->line);
	free(gbl);
	exit(g_exit_status);
}
