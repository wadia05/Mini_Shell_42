/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_complet_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 04:06:25 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/05 05:13:05 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cammand	*create_new_command(void)
{
	t_cammand	*new_cmd;

	new_cmd = malloc(sizeof(t_cammand));
	if (new_cmd == NULL)
	{
		print_error("ERROR: ", "malloc failed\n", "");
		return (NULL);
	}
	new_cmd->args = malloc(sizeof(char *) * BUFFER_SIZE);
	if (new_cmd->args == NULL)
	{
		print_error("ERROR: ", "malloc failed", "");
		free(new_cmd);
		return (NULL);
	}
	new_cmd->args[0] = NULL;
	new_cmd->type = T_COMMEND;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	advance_to_next_token(t_token **tokens)
{
	if (tokens && *tokens)
		*tokens = (*tokens)->next;
}

void	free_command_context(t_command_context *ctx)
{
	if (ctx != NULL)
	{
		if (ctx->current_cmd != NULL)
		{
			free(ctx->current_cmd);
			ctx->current_cmd = NULL;
		}
		if (ctx->head_cmd != NULL)
		{
			free(ctx->head_cmd);
			ctx->head_cmd = NULL;
		}
		if (ctx->final_cmd != NULL)
		{
			free(ctx->final_cmd);
			ctx->final_cmd = NULL;
		}
		free(ctx);
	}
}

void	free_command(t_cammand *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	if (cmd->args != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->next != NULL)
	{
		free_command(cmd->next);
	}
	free(cmd);
}

t_cammand	*process_pipe_tokens(t_token **tokens, t_command_context *ctx)
{
	finalize_commands(&ctx->current_cmd, &ctx->final_cmd, &ctx->head_cmd,
		&ctx->idx);
	ctx->current_cmd = create_pipe_command(&ctx->current_cmd, &ctx->head_cmd);
	if (ctx->current_cmd == NULL)
		return (NULL);
	advance_to_next_token(tokens);
	if ((*tokens)->type == T_PIPE || (*tokens)->value[0] == '\0')
	{
		print_error("", "", "syntax error near unexpected token `|'");
		free_command(ctx->head_cmd);
		return (NULL);
	}
	if (*tokens && ((*tokens)->type == T_DLESS || (*tokens)->type == T_LESS
			|| (*tokens)->type == T_DGREAT || (*tokens)->type == T_GREAT))
	{
		if ((*tokens)->type == T_DLESS)
			ctx->current_cmd = handle_heredocs(tokens, &ctx->current_cmd,
					&ctx->head_cmd);
		else
			ctx->current_cmd = handle_redirections(tokens, ctx);
		if (ctx->current_cmd == NULL)
			return (NULL);
	}
	return (ctx->current_cmd);
}
