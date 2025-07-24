/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:32:14 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/27 03:35:17 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	while (dst_len < size && dst[dst_len] != '\0')
		++dst_len;
	src_len = 0;
	if (size != 0)
	{
		while ((dst_len + src_len) < (size - 1) && src[src_len] != '\0')
		{
			dst[dst_len + src_len] = src[src_len];
			++src_len;
		}
	}
	if ((src_len + dst_len) < size)
		dst[dst_len + src_len] = '\0';
	while (src[src_len] != '\0')
		++src_len;
	return (src_len + dst_len);
}
