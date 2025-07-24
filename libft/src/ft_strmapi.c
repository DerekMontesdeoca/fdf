/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:33:37 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/29 23:31:45 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <libft/libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*mapped;

	len = ft_strlen(s);
	mapped = malloc(len + 1);
	if (mapped == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		mapped[i] = f(i, s[i]);
		++i;
	}
	mapped[i] = '\0';
	return (mapped);
}
