/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:11:56 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/07 03:29:32 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <stdbool.h>
#include <stdlib.h>

static void	free_split(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		strs[i] = NULL;
		++i;
	}
	free(strs);
}

static bool	split(char **strs, size_t len, const char *s, unsigned char c)
{
	size_t	i;
	size_t	n;
	size_t	start;

	n = 0;
	i = 0;
	while (n < len)
	{
		while ((unsigned char) s[i] == c)
			++i;
		start = i;
		while ((unsigned char) s[i] != c && (unsigned char) s[i] != '\0')
			++i;
		strs[n] = ft_substr(s, start, i - start);
		if (strs[n] == NULL)
			return (false);
		if (s[i] == '\0')
			break ;
		++n;
	}
	return (true);
}

static size_t	count_strings(const char *s, unsigned char c)
{
	size_t	n_strs;
	bool	on_str;
	size_t	i;

	n_strs = 0;
	on_str = false;
	i = 0;
	while (s[i] != '\0')
	{
		if (((unsigned char)s[i] != c) != on_str)
		{
			on_str = !on_str;
			n_strs += on_str;
		}
		++i;
	}
	return (n_strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_strs;
	char	**strs;

	n_strs = count_strings(s, c);
	strs = ft_calloc(n_strs + 1, sizeof(char *));
	if (strs == NULL)
		return (NULL);
	if (!split(strs, n_strs, s, c))
	{
		free_split(strs);
		return (NULL);
	}
	return (strs);
}
