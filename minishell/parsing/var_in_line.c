/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_in_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 01:17:11 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 01:22:51 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_char(char *result, char c)
{
	char	current[2];
	char	*temp;

	current[0] = c;
	current[1] = '\0';
	temp = ft_strjoin(result, current);
	free(result);
	return (temp);
}

char	*process_dollar_sign(char *line, t_env *env, t_vars *vars)
{
	char	*temp;

	if (line[vars->i] == '$' && vars->single == 0)
	{
		if (line[vars->i + 1] == '?')
		{
			temp = ft_itoa(g_exit_status);
			vars->result = ft_strjoin(vars->result, temp);
			free(temp);
			vars->i++;
		}
		else
		{
			vars->result = handle_dollar_sign(line, &vars->i, env,
					vars->result);
		}
	}
	else
	{
		vars->result = append_char(vars->result, line[vars->i]);
	}
	return (vars->result);
}

int	handles_quotes(char *line, t_vars *vars)
{
	if (line[vars->i] == '\'' && vars->dble == 0)
	{
		vars->single = !vars->single;
		return (1);
	}
	else if (line[vars->i] == '\"' && vars->single == 0)
	{
		vars->dble = !vars->dble;
		return (1);
	}
	return (0);
}

void	init_vars(t_vars *vars)
{
	vars->result = ft_strdup("");
	vars->temp = NULL;
	vars->i = 0;
	vars->single = 0;
	vars->dble = 0;
}

char	*var_in_line(char *line, t_env *env)
{
	t_vars	vars;

	init_vars(&vars);
	while (line[vars.i])
	{
		if (!handles_quotes(line, &vars))
		{
			vars.result = process_dollar_sign(line, env, &vars);
		}
		if (!vars.result)
			return (NULL);
		vars.i++;
	}
	if (vars.dble == 1 || vars.single == 1)
		return (NULL);
	return (vars.result);
}
