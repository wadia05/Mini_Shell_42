/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:59:17 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/04 09:59:18 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	f;

	f = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == f)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == f)
		return ((char *)s + i);
	return (NULL);
}
