/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:20:25 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/29 22:50:02 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <libft/libft.h>

static char	*write_nbr(int n, bool is_negative, int magnitude, int len)
{
	char	*str;
	int		i;

	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (is_negative)
		str[i++] = '-';
	while (magnitude != 0)
	{
		str[i++] = n / magnitude + '0';
		n %= magnitude;
		magnitude /= 10;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		magnitude;
	bool	is_negative;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	is_negative = n < 0;
	if (is_negative)
		n = -n;
	len = is_negative + 1;
	magnitude = 10;
	while (n >= magnitude && magnitude < 1000000000)
	{
		++len;
		magnitude *= 10;
	}
	if (n < magnitude)
		magnitude /= 10;
	else
		++len;
	return (write_nbr(n, is_negative, magnitude, len));
}
