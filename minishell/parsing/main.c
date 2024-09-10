/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 02:38:05 by med-dahr          #+#    #+#             */
/*   Updated: 2024/09/05 04:01:06 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_exit_status = 0;

void	handle_empty_line(t_globale *gbl)
{
	if (gbl->line == NULL || *gbl->line == '\0')
	{
		if (gbl->line)
			free(gbl->line);
		return ;
	}
	add_history(gbl->line);
}

int	process_input_line(t_globale *gbl)
{
	gbl->s_line = ft_strtrim(gbl->line, " \t");
	free(gbl->line);
	if (gbl->s_line[0] == '\0')
	{
		free(gbl->s_line);
		return (0);
	}
	return (1);
}

int	parse_and_execute(t_globale *gbl)
{
	t_cammand	*cmd;

	gbl->parsed_commands = parsing(gbl->s_line, gbl->my_en);
	if (gbl->parsed_commands == NULL)
	{
		free(gbl->s_line);
		return (0);
	}
	free(gbl->s_line);
	cmd = gbl->parsed_commands;
	gbl->commands = gbl->parsed_commands;
	execute_pipeline(gbl);
	if (cmd != NULL)
		free_commands(cmd);
	cmd = NULL;
	return (1);
}

void	start_shell(t_globale *gbl)
{
	while (1)
	{
		gbl->line = readline(RED "minishell> " RS);
		if (gbl->line == NULL)
			exit_shell(gbl);
		if (*gbl->line == '\0')
		{
			if (gbl->line)
				free(gbl->line);
			continue ;
		}
		if (gbl->my_en == NULL)
			printf("no env\n");
		handle_empty_line(gbl);
		if (!gbl->line)
			continue ;
		if (!process_input_line(gbl))
			continue ;
		if (!parse_and_execute(gbl))
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_globale	*gbl;

	(void)ac;
	(void)av;
	gbl = malloc(sizeof(t_globale));
	if (gbl == NULL)
		return (1);
	setup_signals();
	init_var(gbl, env);
	start_shell(gbl);
	return (g_exit_status);
}
