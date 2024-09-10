/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 01:26:39 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 03:45:13 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_cote(char *value)
{
	int	i;

	i = 0;
	while (value[i] == '\'' || value[i] == '"')
	{
		if (value[i] == '\'' || value[i] == '"')
			return (i);
		i++;
	}
	return (0);
}

// function to handle heredocs, pipes, and redirections
void	initialize_commands(t_cammand **head_cmd, t_cammand **current_cmd,
		t_cammand **final_cmd, int *idx)
{
	*head_cmd = NULL;
	*current_cmd = NULL;
	*final_cmd = NULL;
	*idx = 0;
}

void	finalize_commands(t_cammand **current_cmd, t_cammand **final_cmd,
		t_cammand **head_cmd, int *idx)
{
	if (*final_cmd && *idx > 0)
	{
		(*final_cmd)->args[*idx] = NULL;
		if (*current_cmd)
		{
			(*current_cmd)->next = *final_cmd;
		}
		else
		{
			*head_cmd = *final_cmd;
		}
		*current_cmd = *final_cmd;
		*final_cmd = NULL;
		*idx = 0;
	}
}

void	process_operator_token(t_token **tokens, t_command_context *ctx)
{
	if ((*tokens)->type == T_DLESS)
	{
		ctx->current_cmd = handle_heredocs(tokens, &ctx->current_cmd,
				&ctx->head_cmd);
	}
	else if ((*tokens)->type == T_PIPE)
	{
		ctx->current_cmd = handle_pipes(tokens, ctx);
	}
	else if ((*tokens)->type == T_LESS || (*tokens)->type == T_DGREAT
		|| (*tokens)->type == T_GREAT)
	{
		ctx->current_cmd = handle_redirections(tokens, ctx);
	}
}

void	process_argument_token(t_token **tokens, t_cammand **final_cmd,
		t_cammand **head_cmd, int *idx)
{
	t_cammand	*tmp;

	if (!*final_cmd)
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
		}
	}
	(*final_cmd)->args[*idx] = ft_strdup((*tokens)->value);
	(*idx)++;
	*tokens = (*tokens)->next;
}
