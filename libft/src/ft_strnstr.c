/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:17:30 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/07 03:53:33 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (i + j < len && little[j] != '\0' && big[i + j] == little[j]
			&& big[i + j] != '\0')
			++j;
		if (little[j] == '\0')
			return ((char *)big + i);
		if (big[i + j] == '\0')
			return (NULL);
		++i;
	}
	return (NULL);
}
