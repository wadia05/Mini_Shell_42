/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:12:42 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/04 10:12:46 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nega;
	int	rlt;

	i = 0;
	nega = 1;
	rlt = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			nega = -nega;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		rlt = rlt * 10 + (str[i] - 48);
		i++;
	}
	return (rlt * nega);
}
