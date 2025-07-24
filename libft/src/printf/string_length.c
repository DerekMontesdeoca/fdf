/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:17:55 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/10 14:36:02 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	hex_len(size_t n)
{
	size_t	magnitude;
	size_t	n_digits;

	if (n >= 0x1000000000000000)
		return (16);
	n_digits = 1;
	magnitude = 0x10;
	while (n >= magnitude)
	{
		++n_digits;
		magnitude *= 0x10;
	}
	return (n_digits);
}

size_t	strnlen(const char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < n)
		++i;
	return (i);
}

size_t	uint_len(unsigned int n)
{
	unsigned int	magnitude;
	size_t			n_digits;

	if (n >= 1000000000)
		return (10);
	magnitude = 10;
	n_digits = 1;
	while (n >= magnitude)
	{
		++n_digits;
		magnitude *= 10;
	}
	return (n_digits);
}
