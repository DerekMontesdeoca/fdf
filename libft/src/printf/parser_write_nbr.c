/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_write_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:30:27 by dmontesd          #+#    #+#             */
/*   Updated: 2025/03/24 01:42:05 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "parser_private.h"
#include "string_length.h"

static void	sign_modifier(t_parser *p, int n);

void	parser_write_hex(t_parser *p, bool upper)
{
	unsigned int	n;
	size_t			len;
	size_t			field_len;

	p->token_meta.flags &= (FLAG_ZERO | FLAG_MINUS | FLAG_HASH);
	n = va_arg(*p->ap, unsigned int);
	len = hex_len(n);
	if (p->token_meta.precision == 0 && n == 0)
		len = 0;
	field_len = len;
	if (p->token_meta.precision >= 0 && (size_t)p->token_meta.precision > len)
		field_len = p->token_meta.precision;
	if (len > 0 && p->token_meta.flags & FLAG_HASH && n != 0)
		field_len += 2;
	width_padding(p, field_len, PAD_LEFT);
	alt_hex(p, len, upper, n);
	zero_precision_padding(p, len);
	zero_width_padding(p, field_len);
	writer_write_hex(p->writer, n, len, upper);
	width_padding(p, field_len, PAD_RIGHT);
}

void	parser_write_uint(t_parser *p)
{
	unsigned int	n;
	size_t			len;
	size_t			field_len;

	p->token_meta.flags &= (FLAG_MINUS | FLAG_ZERO);
	n = va_arg(*p->ap, unsigned int);
	len = uint_len(n);
	if (p->token_meta.precision == 0 && n == 0)
		len = 0;
	field_len = len;
	if (p->token_meta.precision >= 0 && (size_t)p->token_meta.precision > len)
		field_len = p->token_meta.precision;
	width_padding(p, field_len, PAD_LEFT);
	zero_width_padding(p, field_len);
	zero_precision_padding(p, len);
	writer_write_uint(p->writer, n, len);
	width_padding(p, field_len, PAD_RIGHT);
}

void	parser_write_int(t_parser *p)
{
	int				n;
	size_t			len;
	size_t			field_len;
	unsigned int	un;

	n = va_arg(*p->ap, int);
	if (n == INT_MIN || n >= 0)
		un = n;
	else
		un = -n;
	len = uint_len(un);
	if (p->token_meta.precision == 0 && n == 0)
		len = 0;
	field_len = len;
	if (p->token_meta.precision >= 0 && (size_t)p->token_meta.precision > len)
		field_len = p->token_meta.precision;
	field_len += n < 0 || (p->token_meta.flags & (FLAG_PLUS | FLAG_SPACE));
	width_padding(p, field_len, PAD_LEFT);
	sign_modifier(p, n);
	zero_precision_padding(p, len);
	zero_width_padding(p, field_len);
	writer_write_uint(p->writer, un, len);
	width_padding(p, field_len, PAD_RIGHT);
}

void	parser_write_pointer_address(t_parser *p)
{
	size_t	address;
	size_t	len;

	p->token_meta.flags &= FLAG_MINUS;
	p->token_meta.precision = FLAG_NOT_SET;
	address = (size_t)va_arg(*p->ap, void *);
	if (address == 0)
		len = 5;
	else
		len = hex_len(address) + 2;
	width_padding(p, len, PAD_LEFT);
	if (address == 0)
		writer_write_str(p->writer, "(nil)");
	else
	{
		writer_write_str(p->writer, "0x");
		writer_write_hex(p->writer, address, len - 2, false);
	}
	width_padding(p, len, PAD_RIGHT);
}

static void	sign_modifier(t_parser *p, int n)
{
	if ((p->token_meta.flags & FLAG_SPACE) && n >= 0)
		writer_putchar(p->writer, ' ');
	else if ((p->token_meta.flags & FLAG_PLUS) && n >= 0)
		writer_putchar(p->writer, '+');
	else if (n < 0)
		writer_putchar(p->writer, '-');
}
