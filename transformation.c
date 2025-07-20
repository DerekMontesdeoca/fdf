/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:05:16 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 16:05:17 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "fdf.h"

#define MAX_ZOOM 10.0f
#define MIN_ZOOM 0.1f

void	make_transformation_stack(t_transformation_stack *t)
{
	size_t	i;

	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	t->ox = 0;
	t->oy = 0;
	t->oz = 0;
	t->px = 0;
	t->tx = 0;
	t->ty = 0;
	t->tz = 0;
	t->projection.zoom_factor = 1.0f;
	t->projection.type = PERSPECTIVE_ORTHO;
	t->projection.pan_x = 0;
	t->projection.pan_y = 0;
	i = 0;
	while (i < M_COUNT)
	{
		t->dirty[i] = true;
		identity_matrix4(t->matrices[i]);
		identity_matrix4(t->results[i]);
		++i;
	}
}

void	transformation_stack_translate(
	t_transformation_stack *t,
	float dx, float dy, float dz
) {
	(void)dz;
	t->dirty[M_TB] = true;
	t->tx += dx;
	t->ty += dy;
	t->tz += dz;
}

void	transformation_stack_pan(
	t_transformation_stack *t,
	float dx, float dy, float dz
) {
	(void)dz;
	t->dirty[M_PROJECTION] = true;
	t->projection.pan_x += dx;
	t->projection.pan_y += dy;
}

void	transformation_stack_origin(
	t_transformation_stack *t,
	float dx, float dy, float dz
) {
	t->dirty[M_ORIGIN] = true;
	t->ox += dx;
	t->oy += dy;
	t->oz += dz;
}

void	transformation_stack_zoom(t_transformation_stack *t, int direction)
{
	double	val;

	t->dirty[M_PROJECTION] = true;
	val = exp((double)direction * 0.1);
	if (t->projection.zoom_factor * val >= MIN_ZOOM
		&& t->projection.zoom_factor * val <= MAX_ZOOM)
		t->projection.zoom_factor *= (float)val;
}
