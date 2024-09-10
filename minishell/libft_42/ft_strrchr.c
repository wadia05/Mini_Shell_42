/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:01:12 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/04 10:01:13 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	f;
	int		x;

	f = (unsigned char)c;
	x = ft_strlen(s);
	while (x >= 0)
	{
		if (s[x] == f)
		{
			return ((char *)s + x);
		}
		x--;
	}
	return (NULL);
}
