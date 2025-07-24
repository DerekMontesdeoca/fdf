/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:06:15 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/07 04:25:35 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "parser_private.h"

static void	parser_initialize(
		t_parser *parser,
		const char *format_str,
		va_list *params,
		t_writer *buf_out
) {
	parser->writer = buf_out;
	parser->index = 0;
	parser->format = format_str;
	parser->ap = params;
	ft_memset(&parser->token_meta, 0, sizeof(t_token_meta));
}

int	parser_parse_and_write(
		t_parser *parser,
		const char *format_str,
		va_list *params,
		t_writer *buf_out
) {
	size_t	token_idx;

	parser_initialize(parser, format_str, params, buf_out);
	writer_reset(parser->writer);
	while (parser->format[parser->index] != '\0')
	{
		if (parser->format[parser->index] != '%')
		{
			writer_putchar(parser->writer, parser->format[parser->index]);
			++parser->index;
		}
		else
		{
			token_idx = ++parser->index;
			if (!parser_process_token(parser))
			{
				writer_putchar(parser->writer, '%');
				parser->index = token_idx;
			}
		}
	}
	writer_flush(parser->writer);
	if (parser->writer->error < 0)
		return (parser->writer->error < 0);
	return (parser->writer->n_written);
}
