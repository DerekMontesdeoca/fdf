/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:59:23 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 18:33:47 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libft/libft.h"

#define CUTOFF 214748364
#define HEXTABLE "0123456789abcdef"

static inline bool	ft_is_negative(const char *str, size_t *i, size_t max)
{
	bool	is_negative;

	is_negative = false;
	if (*i <= max && (str[*i] == '+' || str[*i] == '-'))
	{
		is_negative = str[*i] == '-';
		++*i;
	}
	return (is_negative);
}

int	ft_strntoi(int *n, char *str, size_t max)
{
	size_t			i;
	bool			is_negative;
	unsigned int	nlim;
	unsigned int	accumulator;

	i = 0;
	is_negative = ft_is_negative(str, &i, max);
	nlim = 7;
	if (is_negative)
		nlim = 8;
	if (!ft_isdigit(str[i]))
		return (0);
	accumulator = 0;
	while (i <= max && ft_isdigit(str[i]))
	{
		if (accumulator > CUTOFF || (accumulator == CUTOFF
				&& (unsigned int)(str[i] - '0') > nlim))
			break ;
		accumulator = accumulator * 10 + (str[i] - '0');
		++i;
	}
	*n = (int)accumulator;
	if (is_negative)
		*n = (int)-accumulator;
	return ((int)i);
}

static inline bool	skip_prefix(char **str, char *end)
{
	if (*str != end && **str == '0')
	{
		++*str;
		if (*str == end || (**str != 'x' && **str != 'X'))
			return (false);
		++*str;
	}
	return (true);
}

int	strntohex(uint32_t *n, char *str, char *end)
{
	uint32_t			num;
	char				*found;
	int					i;
	bool				done;

	if (!skip_prefix(&str, end) || str == end)
		return (false);
	num = 0;
	i = 0;
	done = false;
	while (i < 8)
	{
		found = ft_strchr(HEXTABLE, ft_tolower(*str));
		if (!found)
			done = true;
		if (!found)
			break ;
		num = (num << 4) | (found - HEXTABLE);
		++i;
		++str;
	}
	if (!done)
		return (0);
	*n = num;
	return (i + 2);
}
