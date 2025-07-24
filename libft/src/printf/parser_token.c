/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:12:56 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/09 17:16:20 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"

static bool	parser_write_token(t_parser *p);
static void	parser_filter_token_options(t_parser *p);
static void	parser_write_percent(t_parser *p);

bool	parser_process_token(t_parser *p)
{
	parser_parse_flags(p);
	parser_parse_width(p);
	parser_parse_precision(p);
	parser_filter_token_options(p);
	if (!parser_parse_conversion_specifier(p))
		return (false);
	parser_write_token(p);
	return (true);
}

static void	parser_filter_token_options(t_parser *p)
{
	if (p->token_meta.width == PARAM_ASTERISK)
	{
		p->token_meta.width = va_arg(*p->ap, int);
		if (p->token_meta.width < 0)
		{
			p->token_meta.width *= -1;
			p->token_meta.flags |= FLAG_MINUS;
		}
	}
	if (p->token_meta.precision == PARAM_ASTERISK)
	{
		p->token_meta.precision = va_arg(*p->ap, int);
		if (p->token_meta.precision < 0)
			p->token_meta.precision = FLAG_NOT_SET;
	}
	if (p->token_meta.flags & FLAG_ZERO && p->token_meta.flags & FLAG_MINUS)
		p->token_meta.flags &= ~FLAG_ZERO;
	if (p->token_meta.flags & FLAG_PLUS && p->token_meta.flags & FLAG_SPACE)
		p->token_meta.flags &= ~FLAG_SPACE;
	if (p->token_meta.precision >= 0 && (p->token_meta.flags & FLAG_ZERO))
		p->token_meta.flags &= ~FLAG_ZERO;
}

static bool	parser_write_token(t_parser *p)
{
	if (p->token_meta.specifier == 'c')
		parser_write_char(p);
	else if (p->token_meta.specifier == 's')
		parser_write_string(p);
	else if (p->token_meta.specifier == 'p')
		parser_write_pointer_address(p);
	else if (p->token_meta.specifier == 'd')
		parser_write_int(p);
	else if (p->token_meta.specifier == 'i')
		parser_write_int(p);
	else if (p->token_meta.specifier == 'u')
		parser_write_uint(p);
	else if (p->token_meta.specifier == 'x')
		parser_write_hex(p, false);
	else if (p->token_meta.specifier == 'X')
		parser_write_hex(p, true);
	else if (p->token_meta.specifier == '%')
		parser_write_percent(p);
	else
		return (false);
	return (true);
}

static void	parser_write_percent(t_parser *p)
{
	writer_putchar(p->writer, '%');
}
