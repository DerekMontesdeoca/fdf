/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:22:13 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/29 01:49:50 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = c;
	while (*s != '\0')
	{
		if ((unsigned char)*s == uc)
			return ((char *)s);
		++s;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}
