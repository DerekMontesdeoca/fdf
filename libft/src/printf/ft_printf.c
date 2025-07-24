/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:07:27 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/07 04:25:03 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "writer.h"

int	ft_vfprintf(int fd, const char *format, va_list *ap)
{
	static t_writer			buf_out;
	int						return_value;
	t_parser				parser;

	if (format == NULL || fd < 0)
		return (-1);
	buf_out.fd = fd;
	return_value = parser_parse_and_write(&parser, format, ap, &buf_out);
	return (return_value);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		return_value;

	va_start(ap, format);
	return_value = ft_vfprintf(fd, format, &ap);
	va_end(ap);
	return (return_value);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		return_value;

	va_start(ap, format);
	return_value = ft_vfprintf(1, format, &ap);
	va_end(ap);
	return (return_value);
}
