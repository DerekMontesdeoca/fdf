/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:43:15 by dmontesd          #+#    #+#             */
/*   Updated: 2025/02/09 17:10:31 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h"
#include "string_length.h"

void	width_padding(t_parser *p, size_t len, t_padding_position pos)
{
	bool				needs_padding;
	t_padding_position	pad_position;

	needs_padding = (size_t) p->token_meta.width > len
		&& !(p->token_meta.flags & FLAG_ZERO);
	if (p->token_meta.flags & FLAG_MINUS)
		pad_position = PAD_RIGHT;
	else
		pad_position = PAD_LEFT;
	if (needs_padding && (pad_position == pos))
		writer_pad_with(p->writer, ' ', p->token_meta.width - len);
}

void	zero_precision_padding(t_parser *p, size_t len)
{
	if (p->token_meta.precision >= 0 && (size_t)p->token_meta.precision > len)
		writer_pad_with(
			p->writer,
			'0',
			(size_t)p->token_meta.precision - len);
}

void	zero_width_padding(t_parser *p, size_t len)
{
	if (p->token_meta.flags & FLAG_ZERO && (size_t)p->token_meta.width > len)
		writer_pad_with(
			p->writer,
			'0',
			(size_t)p->token_meta.width - len);
}
