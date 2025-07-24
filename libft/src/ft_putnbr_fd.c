/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:40:57 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/30 03:28:36 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <libft/libft.h>

#define BUF_SIZE 12

static void	write_digits(int n, char *buf, bool is_negative, int magnitude)
{
	int	i;

	i = 0;
	if (is_negative)
		buf[i++] = '-';
	while (magnitude != 0)
	{
		buf[i] = (n / magnitude) + '0';
		n %= magnitude;
		magnitude /= 10;
		++i;
	}
	buf[i] = '\0';
}

static int	stack_itoa(int n, char *buf)
{
	int		len;
	int		magnitude;
	bool	is_negative;

	if (n == INT_MIN)
		return (ft_strlcpy(buf, "-2147483648", BUF_SIZE));
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
	if (n >= magnitude)
		++len;
	else
		magnitude /= 10;
	write_digits(n, buf, is_negative, magnitude);
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[BUF_SIZE];
	int		len;

	len = stack_itoa(n, str);
	write(fd, str, len);
}

#undef BUF_SIZE
