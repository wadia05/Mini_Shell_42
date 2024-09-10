/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:18:20 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/04 10:18:23 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*aloo;
	size_t	i;
	size_t	size_to_allocate;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		size_to_allocate = 0;
	else if (ft_strlen(s + start) < len)
		size_to_allocate = ft_strlen(s + start);
	else
		size_to_allocate = len;
	aloo = malloc(size_to_allocate + 1);
	if (aloo == NULL)
		return (NULL);
	while (len > i && start < ft_strlen(s))
	{
		aloo[i] = s[start++];
		i++;
	}
	aloo[i] = '\0';
	return (aloo);
}
