/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:03:54 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/07 20:02:51 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && needle && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)(haystack));
	while (haystack[i] != '\0' && len > 0)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0'
			&& (j < len))
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
		j = 0;
		len--;
	}
	return (NULL);
}
