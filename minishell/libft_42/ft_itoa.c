/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:24:26 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/07 18:41:35 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cont(int k)
{
	int	i;

	i = 0;
	if (k < 0)
	{
		k = (-k);
		i++;
	}
	while (k != 0)
	{
		k = k / 10;
		i++;
	}
	return (i);
}

static char	*ita(int size, int n)
{
	char	*p;

	p = malloc(size + 1);
	if (p == NULL)
		return (NULL);
	p[size] = '\0';
	if (n < 0)
	{
		n = (-n);
		p[0] = '-';
	}
	while (n > 0)
	{
		size--;
		p[size] = (n % 10) + '0';
		n = n / 10;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		size;

	if (n == 0)
	{
		p = malloc(2);
		if (p == NULL)
			return (NULL);
		p[0] = '0';
		p[1] = '\0';
		return (p);
	}
	else if (n == -2147483648)
	{
		p = malloc(12);
		if (p == NULL)
			return (NULL);
		ft_strlcpy(p, "-2147483648", 12);
		return (p);
	}
	size = cont(n);
	p = ita(size, n);
	return (p);
}
