/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 01:17:34 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 04:20:20 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_parse_vars *vars)
{
	t_token	*tmp;

	while (vars->tkn != NULL)
	{
		tmp = vars->tkn;
		vars->tkn = vars->tkn->next;
		free(tmp->value);
		free(tmp);
	}
}

// Main loop to parse the input line, handling tokens and operators.
void	parsing_loop(char *line, t_parse_vars *vars, t_env *my_en)
{
	vars->i = 0;
	vars->in_quotes = 0;
	vars->quote_char = 0;
	vars->tkn = NULL;
	vars->token_start = line;
	while (line[vars->i] != '\0')
	{
		handle_quotes(line, vars);
		if (!vars->in_quotes && (line[vars->i] == ' ' || line[vars->i] == '|'
				|| line[vars->i] == '<' || line[vars->i] == '>'))
		{
			handle_token_creation(line, vars, my_en);
			handle_operator(line, vars, my_en);
			if (vars->tkn == NULL)
				return ;
		}
		vars->i++;
	}
}

// Function to handle final token and syntax error checking
int	handle_finalization(char *line, t_parse_vars *vars, t_env *my_en)
{
	handle_final_token(line, vars, my_en);
	if (vars->in_quotes == 1)
	{
		return (0);
	}
	if (vars->tkn == NULL)
		return (0);
	return (1);
}

// Function to convert tokens to commands and clean up
t_cammand	*convert_and_cleanup(t_parse_vars *vars)
{
	t_cammand	*commands;

	commands = convert_tokens_to_commands(vars->tkn);
	if (commands == NULL)
	{
		g_exit_status = 2;
		free_tokens(vars);
		return (NULL);
	}
	free_tokens(vars);
	return (commands);
}

// Main parsing function that coordinates the entire parsing process.
t_cammand	*parsing(char *line, t_env *my_en)
{
	t_parse_vars	vars;

	vars.token_start = line;
	if (line[0] == '|')
	{
		print_error("", "", "bash: syntax error near unexpected token `|'");
		return (NULL);
	}
	parsing_loop(line, &vars, my_en);
	if (!handle_finalization(line, &vars, my_en))
		return (NULL);
	return (convert_and_cleanup(&vars));
}
