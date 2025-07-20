/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:43:21 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/20 01:43:22 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static inline int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	draw_line_x_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	int		x;
	int		y;
	int		j;
	float	z;

	bresenham->error_count = 2 * bresenham->delta[1] - bresenham->delta[0];
	x = bresenham->p1[0];
	y = bresenham->p1[1];
	z = (float)bresenham->p1[2];
	j = 0;
	while (j <= bresenham->delta[0])
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			screen[y * WINDOW_WIDTH + x] = ((uint32_t)z << 8) & 0xff00;
		x += bresenham->step[0];
		bresenham->error_count += 2 * bresenham->delta[1];
		if (bresenham->error_count > 0)
		{
			y += bresenham->step[1];
			bresenham->error_count -= 2 * bresenham->delta[0];
		}
		z += (float)bresenham->delta[2] / (float)bresenham->delta[0];
		++j;
	}
}

void	draw_line_y_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	int		x;
	int		y;
	int		i;
	float	z;

	bresenham->error_count = 2 * bresenham->delta[1] - bresenham->delta[0];
	x = bresenham->p1[0];
	y = bresenham->p1[1];
	i = 0;
	z = (float)bresenham->p1[2];
	while (i <= bresenham->delta[1])
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			screen[y * WINDOW_WIDTH + x] = ((uint32_t)z << 8) & 0xff00;
		y += bresenham->step[1];
		bresenham->error_count += 2 * bresenham->delta[0];
		if (bresenham->error_count > 0)
		{
			x += bresenham->step[0];
			bresenham->error_count -= 2 * bresenham->delta[1];
		}
		z += (float)bresenham->delta[2] / (float)bresenham->delta[1];
		++i;
	}
}

void	bresenham_init(t_bresenham_state *b, t_point4 *p1, t_point4 *p2)
{
	b->p1[0] = (int) roundf((p1->x + 1) / 2 * WINDOW_WIDTH);
	b->p1[1] = (int) roundf((1 - p1->y) / 2 * WINDOW_HEIGHT);
	b->p1[2] = (int) fminf(fmaxf(((p1->z + 1) / 2.0f * 255.0f) + 50, 0), 255);
	b->p2[0] = (int) roundf((p2->x + 1) / 2 * WINDOW_WIDTH);
	b->p2[1] = (int) roundf((1 - p2->y) / 2 * WINDOW_HEIGHT);
	b->p2[2] = (int) fminf(fmax(((p2->z + 1) / 2.0f * 255.0f) + 50, 0), 255);
	b->delta[0] = b->p2[0] - b->p1[0];
	b->delta[1] = b->p2[1] - b->p1[1];
	b->delta[2] = b->p2[2] - b->p1[2];
	b->step[0] = 1;
	b->step[1] = 1;
	if (b->delta[0] < 0)
		b->step[0] = -1;
	if (b->delta[1] < 0)
		b->step[1] = -1;
	b->delta[0] = ft_abs(b->p2[0] - b->p1[0]);
	b->delta[1] = ft_abs(b->p2[1] - b->p1[1]);
	b->delta[2] = ft_abs(b->p2[2] - b->p1[2]);
}

void	draw_lines(t_fdf *f)
{
	size_t	i;

	i = 0;
	while (i < f->n_edges)
	{
		bresenham_init(&f->bresenham_state,
			&f->transformed_points[f->edges[i][0]],
			&f->transformed_points[f->edges[i][1]]);
		if (f->bresenham_state.delta[0] >= f->bresenham_state.delta[1])
			draw_line_x_major(&f->bresenham_state,
				(unsigned int *)f->renderer.data);
		else
			draw_line_y_major(&f->bresenham_state,
				(unsigned int *)f->renderer.data);
		++i;
	}
}
