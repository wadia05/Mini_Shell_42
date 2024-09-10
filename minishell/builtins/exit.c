/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:45:03 by wait-bab          #+#    #+#             */
/*   Updated: 2024/09/05 02:27:32 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chek_error(char **optin)
{
	int	i;

	i = 0;
	while (optin[1][i])
	{
		if (ft_isalpha(optin[1][i]))
		{
			printf("exit\n");
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(optin[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
}

int	my_exit(char **args)
{
	if (args[1])
	{
		chek_error(args);
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exit_status = 1;
			return (1);
		}
		printf("exit\n");
		exit(ft_atoi(args[1]));
	}
	printf("exit\n");
	exit(0);
	return (0);
}
