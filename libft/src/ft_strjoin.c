/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:31:40 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/27 01:32:01 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len_1;
	size_t	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	joined = malloc(len_1 + len_2 + 1);
	if (joined == NULL)
		return (NULL);
	ft_memcpy(joined, s1, len_1);
	ft_memcpy(joined + len_1, s2, len_2 + 1);
	return (joined);
}
