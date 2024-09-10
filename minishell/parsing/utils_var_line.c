/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 21:57:00 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/03 03:43:14 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variable(char *var_name, t_env *env, char *result)
{
	char	*path;
	char	*temp;

	path = find_path(var_name, env);
	if (path != NULL)
	{
		temp = ft_strjoin(result, path);
		free(result);
		result = temp;
	}
	return (result);
}

char	*process_variable(char *line, int *i, t_env *env, char *result)
{
	char	*var_start;
	char	*var_end;
	int		var_len;
	char	*var_name;

	var_start = &line[*i + 1];
	var_end = var_start;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	var_len = var_end - var_start;
	var_name = malloc(var_len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, var_start, var_len + 1);
	result = expand_variable(var_name, env, result);
	free(var_name);
	*i += var_len;
	return (result);
}

// Function to handle the '@' symbol logic
char	*handle_at_symbol(char *line, int *i, char *result)
{
	int	at_count;
	int	j;

	at_count = 0;
	while (line[*i + 1] == '@')
	{
		at_count++;
		(*i)++;
	}
	if (at_count > 1)
	{
		j = 0;
		while (j < at_count - 1)
		{
			result = append_char(result, '@');
			j++;
		}
	}
	return (result);
}

// Function to handle all dollar sign cases
char	*handle_dollar_sign(char *line, int *i, t_env *env, char *result)
{
	char	current[2];
	char	*temp;

	current[0] = line[*i];
	current[1] = '\0';
	if (line[*i + 1] == '@')
	{
		result = handle_at_symbol(line, i, result);
	}
	else if (line[*i + 1] == ' ' || line[*i + 1] == '\0' || line[*i
			+ 1] == '\"')
	{
		temp = ft_strjoin(result, current);
		free(result);
		result = temp;
	}
	else
	{
		result = process_variable(line, i, env, result);
	}
	return (result);
}

t_cammand	*create_new_commande(void)
{
	t_cammand	*new_cmd;

	new_cmd = malloc(sizeof(t_cammand));
	if (new_cmd == NULL)
	{
		print_error("ERROR: ", "", "malloc failed");
		return (NULL);
	}
	new_cmd->args = malloc(sizeof(char *) * BUFFER_SIZE);
	if (new_cmd->args == NULL)
	{
		print_error("ERROR: ", "", "malloc failed");
		free(new_cmd);
		return (NULL);
	}
	new_cmd->args[0] = NULL;
	new_cmd->type = T_COMMEND;
	new_cmd->next = NULL;
	return (new_cmd);
}
