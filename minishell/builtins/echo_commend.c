/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_commend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 01:28:00 by wait-bab          #+#    #+#             */
/*   Updated: 2024/08/23 10:45:21 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_print(char **args, int first, int i)
{
	while (args[i])
	{
		if (!first)
			write(1, " ", 1);
		write(1, args[i], ft_strlen(args[i]));
		first = 0;
		i++;
	}
}

void	my_echo(char **args)
{
	int	i;
	int	print_newline;
	int	j;
	int	first;

	i = 1;
	print_newline = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		print_newline = 0;
		i++;
	}
	first = 1;
	echo_print(&*args, first, i);
	if (print_newline)
		write(1, "\n", 1);
	g_exit_status = 0;
}
