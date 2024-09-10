/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:42:23 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 04:05:05 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cammand	*process_redirection_tokens(t_token **tokens,
		t_command_context *ctx)
{
	if ((*tokens)->type == T_DLESS)
		ctx->current_cmd = handle_heredocs(tokens, &ctx->current_cmd,
				&ctx->head_cmd);
	else
		ctx->current_cmd = handle_redirections(tokens, ctx);
	if (ctx->current_cmd == NULL)
		return (NULL);
	return (ctx->current_cmd);
}

void	process_other_tokens(t_token **tokens, t_command_context *ctx)
{
	process_argument_token(tokens, &ctx->final_cmd, &ctx->head_cmd, &ctx->idx);
}

t_cammand	*process_tokens(t_token **tokens, t_command_context *ctx)
{
	while (*tokens)
	{
		if ((*tokens)->type == T_PIPE)
		{
			ctx->current_cmd = process_pipe_tokens(tokens, ctx);
			if (ctx->current_cmd == NULL)
				return (NULL);
		}
		else if ((*tokens)->type == T_DLESS || (*tokens)->type == T_LESS
			|| (*tokens)->type == T_DGREAT || (*tokens)->type == T_GREAT)
		{
			ctx->current_cmd = process_redirection_tokens(tokens, ctx);
			if (ctx->current_cmd == NULL)
				return (NULL);
		}
		else
		{
			process_other_tokens(tokens, ctx);
		}
	}
	finalize_commands(&ctx->current_cmd, &ctx->final_cmd, &ctx->head_cmd,
		&ctx->idx);
	return (ctx->head_cmd);
}

// Assuming validate_tokens is a function to validate token order and structure
t_cammand	*convert_tokens_to_commands(t_token *tokens)
{
	t_command_context	ctx;

	ctx.head_cmd = NULL;
	ctx.current_cmd = NULL;
	ctx.final_cmd = NULL;
	ctx.idx = 0;
	if (!process_tokens(&tokens, &ctx))
		return (NULL);
	return (ctx.head_cmd);
}
