/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_update_projection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 02:56:06 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/20 02:56:09 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "fdf.h"

static inline void	projection_fit_box(t_projection_ctl *p)
{
	float	window_ratio;
	float	object_ratio;

	window_ratio = WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	object_ratio = p->box[0] / p->box[1];
	if (object_ratio < window_ratio)
		p->box[0] = window_ratio * p->box[1];
	else if (object_ratio > window_ratio)
		p->box[1] = p->box[0] / window_ratio;
	p->l = -p->box[0] / 2 * p->zoom_factor + p->pan_x;
	p->r = p->box[0] / 2 * p->zoom_factor + p->pan_x;
	p->t = -p->box[1] / 2 * p->zoom_factor + p->pan_y;
	p->b = p->box[1] / 2 * p->zoom_factor + p->pan_y;
	p->n = 0.1f;
	p->f = p->box[2] * 2;
}

void	transformation_update_projection(t_transformation_stack *t)
{
	t_projection_ctl	*proj;

	if (!t->dirty[M_PROJECTION])
		return ;
	if (t->projection.type == PERSPECTIVE_ORTHO)
	{
		proj = &t->projection;
		projection_fit_box(proj);
		identity_matrix4(t->results[M_PROJECTION]);
		t->results[M_PROJECTION][0] = 2.0f / (proj->r - proj->l);
		t->results[M_PROJECTION][5] = 2.0f / (proj->t - proj->b);
		t->results[M_PROJECTION][10] = -2.0f / (proj->f - proj->n);
		t->results[M_PROJECTION][3] = -(proj->r + proj->l)
			/ (proj->r - proj->l);
		t->results[M_PROJECTION][7] = -(proj->t + proj->b)
			/ (proj->t - proj->b);
		t->results[M_PROJECTION][11] = -(proj->f + proj->n)
			/ (proj->f - proj->n);
	}
	else
		assert(false && "Unreachable code");
}
