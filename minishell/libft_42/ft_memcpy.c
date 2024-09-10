/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:50:42 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/07 20:01:29 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ds;
	unsigned char	*sc;

	ds = (unsigned char *)dst;
	sc = (unsigned char *)src;
	if (!sc && !ds)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ds[i] = sc[i];
		i++;
	}
	return (dst);
}
