/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:21:36 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 23:34:18 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include "libft/libft.h"

#define FONT_CHAR_0      (uint8_t *)"\x3E\x63\x73\x7B\x6F\x67\x3E\x00"
#define FONT_CHAR_1      (uint8_t *)"\x0C\x0E\x0C\x0C\x0C\x0C\x3F\x00"
#define FONT_CHAR_2      (uint8_t *)"\x1E\x33\x30\x1C\x06\x33\x3F\x00"
#define FONT_CHAR_3      (uint8_t *)"\x1E\x33\x30\x1C\x30\x33\x1E\x00"
#define FONT_CHAR_4      (uint8_t *)"\x38\x3C\x36\x33\x7F\x30\x78\x00"
#define FONT_CHAR_5      (uint8_t *)"\x3F\x03\x1F\x30\x30\x33\x1E\x00"
#define FONT_CHAR_6      (uint8_t *)"\x1C\x06\x03\x1F\x33\x33\x1E\x00"
#define FONT_CHAR_7      (uint8_t *)"\x3F\x33\x30\x18\x0C\x0C\x0C\x00"
#define FONT_CHAR_8      (uint8_t *)"\x1E\x33\x33\x1E\x33\x33\x1E\x00"
#define FONT_CHAR_9      (uint8_t *)"\x1E\x33\x33\x3E\x30\x18\x0E\x00"
#define FONT_CHAR_SPACE  (uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00"
#define FONT_CHAR_F      (uint8_t *)"\x7F\x46\x16\x1E\x16\x06\x0F\x00"
#define FONT_CHAR_P      (uint8_t *)"\x00\x00\x3B\x66\x66\x3E\x06\x0F"
#define FONT_CHAR_S      (uint8_t *)"\x00\x00\x3E\x03\x1E\x30\x1F\x00"
#define FONT_CHAR_COLON  (uint8_t *)"\x00\x0C\x0C\x00\x00\x0C\x0C\x00"
#define FONT_CHAR_PERIOD (uint8_t *)"\x00\x00\x00\x00\x00\x0C\x0C\x00"

static inline uint8_t	*get_char(char c)
{
	if (c == 'F')
		return (FONT_CHAR_F);
	else if (c == 'p')
		return (FONT_CHAR_P);
	else if (c == 's')
		return (FONT_CHAR_S);
	else if (c == ':')
		return (FONT_CHAR_COLON);
	else if (c == '.')
		return (FONT_CHAR_PERIOD);
	else
		return (FONT_CHAR_SPACE);
}

uint8_t	*get_glyph(char c)
{
	if (c == '0')
		return (FONT_CHAR_0);
	else if (c == '1')
		return (FONT_CHAR_1);
	else if (c == '2')
		return (FONT_CHAR_2);
	else if (c == '3')
		return (FONT_CHAR_3);
	else if (c == '4')
		return (FONT_CHAR_4);
	else if (c == '5')
		return (FONT_CHAR_5);
	else if (c == '6')
		return (FONT_CHAR_6);
	else if (c == '7')
		return (FONT_CHAR_7);
	else if (c == '8')
		return (FONT_CHAR_8);
	else if (c == '9')
		return (FONT_CHAR_9);
	else
		return (get_char(c));
}
