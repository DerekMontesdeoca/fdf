/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:42:03 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 18:43:53 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	pack_color(t_bresenham_state *b, int step)
{
	return ((((int)(step * b->color_r_delta)
			+ (b->color1 >> 16 & 0xff)) << 16)
	| (((int)(step * b->color_g_delta)
				+ ((b->color1 >> 8 & 0xff))) << 8)
	| ((int)(step * b->color_b_delta)
				+ (b->color1 & 0xff)));
}
