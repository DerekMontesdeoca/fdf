/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:37:02 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/29 17:25:20 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <libft/libft.h>

static bool	contained_in(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (true);
		++i;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	i = 0;
	while (s1[i] != '\0' && contained_in(s1[i], set))
		++i;
	start = i;
	i += ft_strlen(s1 + i);
	while (i > 0 && contained_in(s1[i - 1], set))
		--i;
	end = i;
	return (ft_substr(s1, start, end - start));
}
