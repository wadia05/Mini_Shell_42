/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:14:37 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/04 10:14:40 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*aloo;
	size_t	i;

	aloo = malloc(count * size);
	if (aloo == NULL)
		return (NULL);
	i = 0;
	while (count * size > i)
	{
		*(char *)(aloo + (i++)) = 0;
	}
	return (aloo);
}
