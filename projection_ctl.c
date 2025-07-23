/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_ctl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:36:15 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 18:37:45 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	make_projection_ctl(
	t_projection_ctl *p,
	float width,
	float height,
	float depth
) {
	float	window_ratio;
	float	object_ratio;
	float	box;
	float	with_margin;

	box = fmaxf(fmaxf(width, height), depth);
	with_margin = box * 2.0f;
	p->box[0] = with_margin;
	p->box[1] = with_margin;
	p->box[2] = with_margin;
	window_ratio = WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	object_ratio = p->box[0] / p->box[1];
	if (object_ratio < window_ratio)
		p->box[0] = window_ratio * p->box[1];
	else if (object_ratio > window_ratio)
		p->box[1] = p->box[0] / window_ratio;
}

void	projection_reset_params(t_projection_ctl *p)
{
	p->zoom_factor = 1;
	p->pan_x = 0;
	p->pan_y = 0;
}
