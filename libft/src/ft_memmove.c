/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:28:46 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/27 01:31:30 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_bytes;
	const unsigned char	*src_bytes;
	size_t				i;

	dest_bytes = dest;
	src_bytes = src;
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			dest_bytes[i - 1] = src_bytes[i - 1];
			--i;
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			dest_bytes[i] = src_bytes[i];
			++i;
		}
	}
	return (dest);
}
