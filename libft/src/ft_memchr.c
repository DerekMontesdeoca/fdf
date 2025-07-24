/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:06:51 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/29 01:56:25 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*memory_area;
	unsigned char	c2;

	memory_area = (unsigned char *)s;
	c2 = c;
	i = 0;
	while (i < n)
	{
		if (memory_area[i] == c2)
			return ((void *) memory_area + i);
		++i;
	}
	return (NULL);
}
