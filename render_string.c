/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:29:23 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/20 02:29:25 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "font.h"

#define SCALE 3

static inline void	render_scaled_bit(t_draw_char_params *p, int row, int col)
{
	int	i;
	int	j;
	int	srow;
	int	scol;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			srow = row * SCALE + i + p->y;
			scol = col * SCALE + j + p->x;
			p->buf[srow * WINDOW_WIDTH + scol] = p->color;
			++j;
		}
		++i;
	}
}

static inline void	render_char(t_draw_char_params *p, char c)
{
	int		row;
	int		col;
	uint8_t	*glyph;

	glyph = (uint8_t *)font8x8_basic[(uint8_t)c];
	row = 0;
	while (row < 8)
	{
		col = 0;
		while (col < 8)
		{
			if (glyph[row] & (1 << col))
				render_scaled_bit(p, row, col);
			++col;
		}
		++row;
	}
}

void	render_string(char *str, uint32_t *buf, int x, int y)
{
	while (*str)
	{
		render_char(&(t_draw_char_params){
			.x = x, .y = y, .buf = buf, .color = 0x00ffffff
		}, *str);
		++str;
		x += 8 * SCALE;
	}
}
