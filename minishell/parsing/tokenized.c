/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenized.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 01:17:55 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 03:41:46 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_value(char *value, t_token *new_token, t_env *env)
{
	int	i;

	i = find_cote(value);
	if (i)
	{
		if (value[0] == '"' && value[strlen(value) - 1] == '"')
		{
			new_token->value = var_in_line(value, env);
		}
		else if (value[0] == '\'' && value[strlen(value) - 1] == '\'')
		{
			new_token->value = ft_strndup(value + 1, strlen(value) - 2);
		}
		else
		{
			new_token->value = var_in_line(value, env);
		}
	}
	else
	{
		new_token->value = var_in_line(value, env);
	}
}

// Checks if the token value is valid, freeing the token if it is not.
int	check_token_value(t_token *new_token)
{
	if (new_token->value == NULL)
	{
		free(new_token);
		return (0);
	}
	return (1);
}

void	set_token_type(char *value, t_token *new_token)
{
	if (ft_strncmp(value, "|", 2) == 0)
		new_token->type = T_PIPE;
	else if (ft_strncmp(value, "<", 2) == 0)
		new_token->type = T_LESS;
	else if (ft_strncmp(value, ">", 2) == 0)
		new_token->type = T_GREAT;
	else if (ft_strncmp(value, "<<", 3) == 0)
		new_token->type = T_DLESS;
	else if (ft_strncmp(value, ">>", 3) == 0)
		new_token->type = T_DGREAT;
	else
		new_token->type = T_WORD;
	new_token->next = NULL;
}

// Adds a new token to the end of the token list.
t_token	*add_to_list(t_token *head, t_token *new_token)
{
	t_token	*tmp;

	if (head == NULL)
		return (new_token);
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	return (head);
}

// Creates a new token from the value and adds it to the token list.
t_token	*tokencreate(char *value, t_token *head, t_env *env)
{
	t_token	*new_token;

	(void)env;
	new_token = allocate_new_token();
	if (new_token == NULL)
		return (NULL);
	set_token_value(value, new_token, env);
	if (!check_token_value(new_token))
		return (NULL);
	set_token_type(value, new_token);
	return (add_to_list(head, new_token));
}
