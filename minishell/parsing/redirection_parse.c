/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:37:18 by med-dahr          #+#    #+#             */
/*   Updated: 2024/08/23 01:43:46 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cammand	*create_redirection_command(t_token **tokens, t_cammand **head_cmd)
{
	t_cammand	*redir_cmd;
	t_cammand	*tmp;

	redir_cmd = create_new_command();
	if (redir_cmd == NULL)
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
	redir_cmd->args[0] = strdup((*tokens)->value);
	redir_cmd->args[1] = strdup((*tokens)->next->value);
	redir_cmd->args[2] = NULL;
	redir_cmd->type = (*tokens)->type;
	return (redir_cmd);
}

void	link_redirection_command(t_command_context *ctx, t_cammand *redir_cmd)
{
	if (ctx->head_cmd == NULL)
	{
		ctx->head_cmd = redir_cmd;
	}
	else
	{
		ctx->current_cmd->next = redir_cmd;
	}
	ctx->current_cmd = redir_cmd;
}

t_cammand	*advance_tokens_for_redirection(t_token **tokens,
		t_cammand **current_cmd)
{
	*tokens = (*tokens)->next->next;
	if (*tokens == NULL || (*tokens)->type == T_DLESS
		|| (*tokens)->type == T_PIPE || (*tokens)->type == T_LESS
		|| (*tokens)->type == T_DGREAT || (*tokens)->type == T_GREAT)
	{
		return (*current_cmd);
	}
	return ((t_cammand *)1);
}

t_cammand	*handle_redirections(t_token **tokens, t_command_context *ctx)
{
	t_cammand	*redir_cmd;

	while (*tokens && ((*tokens)->type == T_LESS || (*tokens)->type == T_DGREAT
			|| (*tokens)->type == T_GREAT))
	{
		if (validate_next_token(tokens) == 0)
			return (NULL);
		redir_cmd = create_redirection_command(tokens, &ctx->head_cmd);
		if (redir_cmd == NULL)
			return (NULL);
		link_redirection_command(ctx, redir_cmd);
		if (advance_tokens_for_redirection(tokens, &ctx->current_cmd) == NULL)
			return (ctx->current_cmd);
	}
	return (ctx->current_cmd);
}
