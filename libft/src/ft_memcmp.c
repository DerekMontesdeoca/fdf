/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:51:54 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/27 04:49:06 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		cmp;

	i = 0;
	cmp = 0;
	while (i < n)
	{
		cmp = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (cmp != 0)
			return (cmp);
		++i;
	}
	return (0);
}
