/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_edges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:13:16 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/20 01:13:20 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	init_horizontal_edges(t_fdf *f, int index_start)
{
	int	y;
	int	x;
	int	i;

	x = 0;
	y = 0;
	i = index_start;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width - 1)
		{
			f->edges[i][0] = y * f->width + x;
			f->edges[i][1] = y * f->width + x + 1;
			++x;
			++i;
		}
		++y;
	}
}

static inline void	init_vertical_edges(t_fdf *f, int index_start)
{
	int	y;
	int	x;
	int	i;

	x = 0;
	y = 0;
	i = index_start;
	while (y < f->height - 1)
	{
		x = 0;
		while (x < f->width)
		{
			f->edges[i][0] = y * f->width + x;
			f->edges[i][1] = (y + 1) * f->width + x;
			++x;
			++i;
		}
		++y;
	}
}

void	fdf_init_edges(t_fdf *f)
{
	init_horizontal_edges(f, 0);
	init_vertical_edges(f, (f->width - 1) * f->height);
}
