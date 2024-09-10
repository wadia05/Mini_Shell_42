/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 01:17:41 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 03:48:30 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to initialize the pipe command
t_cammand	*initialize_pipe_command(t_cammand **head_cmd)
{
	t_cammand	*pipe_cmd;
	t_cammand	*tmp;

	pipe_cmd = create_new_command();
	if (pipe_cmd == NULL)
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
	pipe_cmd->args[0] = strdup("|");
	pipe_cmd->args[1] = NULL;
	pipe_cmd->type = T_PIPE;
	return (pipe_cmd);
}

// Function to create and link the pipe command
t_cammand	*create_pipe_command(t_cammand **current_cmd, t_cammand **head_cmd)
{
	t_cammand	*pipe_cmd;

	pipe_cmd = initialize_pipe_command(head_cmd);
	if (pipe_cmd == NULL)
	{
		return (NULL);
	}
	if (*current_cmd)
	{
		(*current_cmd)->next = pipe_cmd;
	}
	else
	{
		*head_cmd = pipe_cmd;
	}
	*current_cmd = pipe_cmd;
	return (*current_cmd);
}

// Function to prepare the next command
t_cammand	*prepare_next_command(t_token **tokens, t_cammand **final_cmd,
		t_cammand **head_cmd)
{
	t_cammand	*tmp;

	if (*tokens && (*tokens)->type != T_PIPE && (*tokens)->type != T_DLESS
		&& (*tokens)->type != T_LESS && (*tokens)->type != T_DGREAT
		&& (*tokens)->type != T_GREAT)
	{
		*final_cmd = create_new_command();
		if (*final_cmd == NULL)
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
	}
	return (*final_cmd);
}

// Function to handle pipes and check for syntax errors
t_cammand	*handle_pipes(t_token **tokens, t_command_context *ctx)
{
	while (*tokens && (*tokens)->type == T_PIPE)
	{
		if ((*tokens)->type == T_PIPE && (*tokens)->next
			&& (*tokens)->next->type == T_PIPE)
		{
			print_error("ERROR: ", "", "syntax error unexpected token `||'");
			return (NULL);
		}
		ctx->current_cmd = finalize_current_command(&ctx->current_cmd,
				&ctx->head_cmd, &ctx->final_cmd, &ctx->idx);
		if (ctx->current_cmd == NULL)
		{
			print_error("ERROR: ", "", "malloc failed");
			return (NULL);
		}
		ctx->current_cmd = create_pipe_command(&ctx->current_cmd,
				&ctx->head_cmd);
		if (ctx->current_cmd == NULL)
			return (NULL);
		advance_to_next_token(tokens);
		if (prepare_next_command(tokens, &ctx->final_cmd,
				&ctx->head_cmd) == NULL)
			return (NULL);
	}
	return (ctx->current_cmd);
}
