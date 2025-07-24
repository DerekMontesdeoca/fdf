/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:25:24 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/30 00:31:29 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <libft/libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	while (i < start && s[i] != '\0')
		++i;
	if (i < start)
		return (ft_calloc(1, 1));
	i = 0;
	while (i < len && s[start + i] != '\0')
		++i;
	substr = malloc(i + 1);
	if (substr == NULL)
		return (NULL);
	substr[i] = '\0';
	return (ft_memcpy(substr, s + start, i));
}
