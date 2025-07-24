/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:25:08 by dmontesd          #+#    #+#             */
/*   Updated: 2025/03/24 01:42:28 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "parser.h"

# define FLAG_MINUS 1
# define FLAG_PLUS 2
# define FLAG_ZERO 4
# define FLAG_HASH 8
# define FLAG_SPACE 16
# define PARAM_ASTERISK -2
# define FLAG_NOT_SET -1

typedef enum e_padding_position
{
	PAD_LEFT,
	PAD_RIGHT,
}	t_padding_position;

bool	parser_process_token(t_parser *p);

/*
 * If specifier is invalid, returns false and sets specifier on token_meta to -1
 */
bool	parser_parse_conversion_specifier(t_parser *p);

/*
 * Returns:
 * 	n if width set on format
 * 	FLAG_NOT_SET if not set
 * 	PARAM_ASTERISK if * param
 */
void	parser_parse_precision(t_parser *p);

/*
 * Sets width to:
 * 	+n if width set on format
 * 	 0 if not set or set to 0 on format
 * 	 PARAM_ASTERISK if * param;
 */
void	parser_parse_width(t_parser *p);

void	parser_parse_flags(t_parser *p);

void	width_padding(t_parser *p, size_t len, t_padding_position pos);

void	zero_precision_padding(t_parser *p, size_t len);

void	zero_width_padding(t_parser *p, size_t len);

void	parser_write_hex(t_parser *p, bool upper);

void	parser_write_uint(t_parser *p);

void	parser_write_int(t_parser *p);

void	parser_write_pointer_address(t_parser *p);

void	parser_write_string(t_parser *p);

void	parser_write_char(t_parser *p);

void	alt_hex(t_parser *p, size_t len, bool upper, unsigned int value);

#endif
