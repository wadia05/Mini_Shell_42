/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 02:06:52 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/05 02:24:36 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(char *line, t_parse_vars *vars)
{
	if ((line[vars->i] == '"' || line[vars->i] == '\'') && (!vars->in_quotes
			|| line[vars->i] == vars->quote_char))
	{
		if (vars->in_quotes)
		{
			vars->in_quotes = 0;
			vars->quote_char = 0;
		}
		else
		{
			vars->in_quotes = 1;
			vars->quote_char = line[vars->i];
		}
	}
}

/* Creates a token from the current segment of 
	the line and adds it to the token list.*/
void	handle_token_creation(char *line, t_parse_vars *vars, t_env *my_en)
{
	char	*token;

	if (vars->token_start < &line[vars->i])
	{
		token = ft_strndup(vars->token_start, &line[vars->i]
				- vars->token_start);
		if (token == NULL)
		{
			print_error("ERROR: ", "", "Memory allocation failed\n");
			return ;
		}
		vars->tkn = tokencreate(token, vars->tkn, my_en);
		free(token);
		if (vars->tkn == NULL)
		{
			print_error("", "", "ERROR\n");
		}
	}
}

// Identifies and processes operators (like <, >, |) in the input line
void	handle_operator(char *line, t_parse_vars *vars, t_env *my_en)
{
	char	operator[3];

	operator[0] = line[vars->i];
	operator[1] = '\0';
	operator[2] = '\0';
	if (line[vars->i] != ' ')
	{
		if ((line[vars->i] == '<' || line[vars->i] == '>') && line[vars->i
				+ 1] == line[vars->i])
		{
			operator[1] = line[vars->i + 1];
			vars->i++;
		}
		vars->tkn = tokencreate(operator, vars->tkn, my_en);
		if (vars->tkn == NULL)
		{
			print_error("", "", "syntax error");
		}
	}
	vars->token_start = &line[vars->i + 1];
}

void	handle_final_token(char *line, t_parse_vars *vars, t_env *my_en)
{
	char	*token;

	if (vars->token_start <= &line[vars->i])
	{
		token = ft_strndup(vars->token_start, &line[vars->i + 1]
				- vars->token_start);
		vars->tkn = tokencreate(token, vars->tkn, my_en);
		free(token);
		if (vars->tkn == NULL)
		{
			g_exit_status = 2;
			print_error("", "", "syntax error");
			return ;
		}
	}
}

void	init_var(t_globale *gbl, char **env)
{
	gbl->my_en = my_env(env);
	gbl->line = NULL;
	gbl->commands = NULL;
	gbl->parsed_commands = NULL;
	gbl->cmd_iter = NULL;
	gbl->n_pipe = 0;
	gbl->s_line = NULL;
	gbl->in_fd = STDIN_FILENO;
	gbl->out_fd = STDOUT_FILENO;
	gbl->pid = -1;
}
