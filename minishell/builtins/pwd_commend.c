/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_commend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 02:07:47 by wait-bab          #+#    #+#             */
/*   Updated: 2024/08/23 12:01:05 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_exit_status = 1;
		return ;
	}
	if (pwd == NULL)
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	g_exit_status = 0;
}
