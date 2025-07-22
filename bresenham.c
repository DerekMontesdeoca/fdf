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
#include <stdio.h>
#include "fdf.h"
#include "libft/libft.h"

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
	uint32_t	color;

	bresenham->error_count = 2 * bresenham->delta[1] - bresenham->delta[0];
	bresenham->color_r_delta /= bresenham->delta[0];
	bresenham->color_g_delta /= bresenham->delta[0];
	bresenham->color_b_delta /= bresenham->delta[0];
	x = bresenham->p1[0];
	y = bresenham->p1[1];
	j = 0;
	color = bresenham->color1;
	while (j <= bresenham->delta[0])
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			screen[y * WINDOW_WIDTH + x] = color;
		x += bresenham->step[0];
		bresenham->error_count += 2 * bresenham->delta[1];
		if (bresenham->error_count > 0)
		{
			y += bresenham->step[1];
			bresenham->error_count -= 2 * bresenham->delta[0];
		}
		color = (((int)(j * bresenham->color_r_delta) + (bresenham->color1 >> 16 & 0xff)) << 16)
			| (((int)(j * bresenham->color_g_delta) + ((bresenham->color1 >> 8 & 0xff))) << 8)
			| ((int)(j * bresenham->color_b_delta) + (bresenham->color1 & 0xff));
		++j;
	}
}

void	draw_line_y_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	int		x;
	int		y;
	int		i;
	uint32_t	color;

	bresenham->color_r_delta /= bresenham->delta[1];
	bresenham->color_g_delta /= bresenham->delta[1];
	bresenham->color_b_delta /= bresenham->delta[1];
	bresenham->error_count = 2 * bresenham->delta[1] - bresenham->delta[0];
	x = bresenham->p1[0];
	y = bresenham->p1[1];
	i = 0;
	color = bresenham->color1;
	while (i <= bresenham->delta[1])
	{
		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			screen[y * WINDOW_WIDTH + x] = color;
		y += bresenham->step[1];
		bresenham->error_count += 2 * bresenham->delta[0];
		if (bresenham->error_count > 0)
		{
			x += bresenham->step[0];
			bresenham->error_count -= 2 * bresenham->delta[1];
		}
		color = (((int)(i * bresenham->color_r_delta) + (bresenham->color1 >> 16 & 0xff)) << 16)
			| (((int)(i * bresenham->color_g_delta) + ((bresenham->color1 >> 8 & 0xff))) << 8)
			| ((int)(i * bresenham->color_b_delta) + (bresenham->color1 & 0xff));
		++i;
	}
}

void	bresenham_init(
	t_bresenham_state *b, t_fdf *fdf, int i
) {
	t_point4	*p1;
	t_point4	*p2;

	p1 = &fdf->transformed_points[fdf->edges[i][0]];
	p2 = &fdf->transformed_points[fdf->edges[i][1]];
	b->color1 = fdf->color[fdf->edges[i][0]];
	b->color2 = fdf->color[fdf->edges[i][1]];
	b->p1[0] = (int) ((p1->x + 1) / 2 * WINDOW_WIDTH);
	b->p1[1] = (int) ((1 - p1->y) / 2 * WINDOW_HEIGHT);
	b->p1[2] = (int) fminf(fmaxf(((p1->z + 1) / 2.0f * 255.0f) + 50, 150), 255);
	b->p2[0] = (int) ((p2->x + 1) / 2 * WINDOW_WIDTH);
	b->p2[1] = (int) ((1 - p2->y) / 2 * WINDOW_HEIGHT);
	b->p2[2] = (int) fminf(fmaxf(((p2->z + 1) / 2.0f * 255.0f) + 50, 150), 255);
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
	b->color_r_delta = (int)(b->color2 >> 16 & 0xff) - (int)(b->color1 >> 16 & 0xff);
	b->color_g_delta = (int)(b->color2 >> 8 & 0xff) - (int)(b->color1 >> 8 & 0xff);
	b->color_b_delta = (int)(b->color2 & 0xff) - (int)(b->color1 & 0xff);
}

static inline bool	test_out(t_point4 *p1, t_point4 *p2)
{
	return ((p1->x < -1 && p2->x < -1)
		|| (p1->x > 1 && p2->x > 1)
		|| (p1->y < -1 && p2->y < -1)
		|| (p1->y > 1 && p2->y > 1)
		|| (p1->z < -1 && p2->z < -1)
		|| (p1->z > 1 && p2->z > 1));
}

/*
 * Stride downscales on zoom out and test in clips points.
 */
void	draw_lines(t_fdf *f)
{
	size_t	i;

	i = 0;
	while (i < f->n_edges)
	{
		if (test_out(&f->transformed_points[f->edges[i][0]], &f->transformed_points[f->edges[i][1]]))
		{
			++i;
			// i = i + (size_t) fmaxf(log2f(f->transformation_stack.projection.zoom_factor * 10.0f), 1.0f);
			continue ;
		}
		bresenham_init(&f->bresenham_state, f, i);
		if (f->bresenham_state.delta[0] >= f->bresenham_state.delta[1])
			draw_line_x_major(&f->bresenham_state,
				(unsigned int *)f->renderer.data);
		else
			draw_line_y_major(&f->bresenham_state,
				(unsigned int *)f->renderer.data);
		++i;
		// i = i + (size_t) fmaxf(log2f(f->transformation_stack.projection.zoom_factor * 10.0f), 1.0f);
	}
}
