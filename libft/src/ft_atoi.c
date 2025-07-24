/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:05:10 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/30 02:57:05 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <limits.h>
#include <stdbool.h>

int	ft_isspace(int c)
{
	unsigned int	uc;

	uc = c;
	return ((uc >= 9 && uc <= 13) || uc == ' ');
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		value;
	bool	is_negative;

	i = 0;
	value = 0;
	while (ft_isspace(nptr[i]))
		++i;
	is_negative = false;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		is_negative = nptr[i] == '-';
		++i;
	}
	while (nptr[i] == '0')
		++i;
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		value *= 10;
		value += nptr[i] - '0';
		++i;
	}
	if (is_negative)
		value = -value;
	return (value);
}
