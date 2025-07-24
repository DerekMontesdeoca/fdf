/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:36:08 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/29 02:35:08 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*last;
	unsigned char		uc;

	uc = c;
	last = NULL;
	while (*s != '\0')
	{
		if ((unsigned char)*s == uc)
			last = (const unsigned char *) s;
		++s;
	}
	if (uc == '\0')
		return ((char *)s);
	return ((char *)last);
}
