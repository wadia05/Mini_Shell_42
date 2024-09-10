/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 05:44:20 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/01 05:34:23 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cammand	*validate_next_token(t_token **tokens)
{
	if ((*tokens)->next == NULL || (*tokens)->next->value == NULL
		|| (*tokens)->next->value[0] == '\0' || (*tokens)->next->value[0] == '<'
		|| (*tokens)->next->value[0] == '>' || (*tokens)->next->value[0] == '|')
	{
		print_error("ERROR: ", "",
			"syntax error near unexpected token `newline'");
		return (NULL);
	}
	return ((t_cammand *)1);
}

t_cammand	*create_heredoc_command(t_token **tokens, t_cammand **head_cmd)
{
	t_cammand	*heredoc_cmd;
	t_cammand	*tmp;

	heredoc_cmd = create_new_command();
	if (heredoc_cmd == NULL)
	{
		while (*head_cmd)
		{
			tmp = *head_cmd;
			*head_cmd = (*head_cmd)->next;
			free(tmp->args);
			free(tmp);
		}
		return (NULL);
	}
	heredoc_cmd->args[0] = ft_strdup("<<");
	heredoc_cmd->args[1] = ft_strdup((*tokens)->next->value);
	heredoc_cmd->args[2] = NULL;
	heredoc_cmd->type = T_DLESS;
	return (heredoc_cmd);
}

void	link_heredoc_command(t_cammand **current_cmd, t_cammand **head_cmd,
		t_cammand *heredoc_cmd)
{
	if (*head_cmd == NULL)
	{
		*head_cmd = heredoc_cmd;
	}
	else
	{
		(*current_cmd)->next = heredoc_cmd;
	}
	*current_cmd = heredoc_cmd;
}

t_cammand	*advance_and_finalize_tokens(t_token **tokens,
		t_cammand **current_cmd)
{
	*tokens = (*tokens)->next->next;
	if (*tokens == NULL || (*tokens)->type == T_DLESS
		|| (*tokens)->type == T_PIPE)
	{
		return (*current_cmd);
	}
	return ((t_cammand *)1);
}

// Function to handle the heredoc input
t_cammand	*handle_heredocs(t_token **tokens, t_cammand **current_cmd,
		t_cammand **head_cmd)
{
	t_cammand	*heredoc_cmd;

	while (*tokens && (*tokens)->type == T_DLESS)
	{
		if (validate_next_token(tokens) == NULL)
			return (NULL);
		heredoc_cmd = create_heredoc_command(tokens, head_cmd);
		if (heredoc_cmd == NULL)
			return (NULL);
		link_heredoc_command(current_cmd, head_cmd, heredoc_cmd);
		if (advance_and_finalize_tokens(tokens, current_cmd) == NULL)
			return (*current_cmd);
	}
	return (*current_cmd);
}
