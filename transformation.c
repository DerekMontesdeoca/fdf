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

#include <stddef.h>
#include "fdf.h"

void	make_transformation_stack(t_transformation_stack *t)
{
	size_t	i;

	t->scale = 1;
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
	t->dirty[M_TB] = true;
	t->tx += dx;
	t->ty += dy;
	t->tz += dz;
}

void	transformation_stack_scale(t_transformation_stack *t, float delta)
{
	t->dirty[M_SCALE] = true;
	t->scale += delta;
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
