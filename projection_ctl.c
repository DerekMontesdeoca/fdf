#include <math.h>
#include "fdf.h"
#include "libft/libft.h"

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