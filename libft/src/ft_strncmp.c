/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:34:11 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/27 01:35:11 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		cmp;

	if (n == 0)
		return (0);
	i = 0;
	cmp = 0;
	while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0')
	{
		cmp = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (cmp != 0)
			return (cmp);
		++i;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
