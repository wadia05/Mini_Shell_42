/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:53:36 by wait-bab          #+#    #+#             */
/*   Updated: 2024/01/04 09:53:37 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*sc;
	unsigned char	*ds;

	sc = (unsigned char *)src;
	ds = (unsigned char *)dst;
	if (!sc && !ds)
		return (NULL);
	i = 0;
	if (ds > sc)
	{
		while (i < len)
		{
			ds[len - 1] = sc[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(ds, sc, len);
	}
	return (ds);
}
