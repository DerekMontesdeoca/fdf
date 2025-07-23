/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:02:13 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 18:34:24 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tgmath.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "mlx.h"
#include "fdf.h"

#define ROTATE_FACTOR 0.09f

int	key_press_handler(const int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		mlx_loop_end(fdf->mlx);
	if (keycode == XK_p)
	{
		transformation_stack_parallel(&fdf->transformation_stack);
		projection_reset_params(&fdf->transformation_stack.projection);
		fdf->transformation_stack.dirty[M_PROJECTION] = true;
		transformation_stack_update(&fdf->transformation_stack);
		center_model(&fdf->transformation_stack, (float)fdf->width,
			(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
	}
	if (keycode == XK_i)
	{
		transformation_stack_isometric(&fdf->transformation_stack);
		projection_reset_params(&fdf->transformation_stack.projection);
		fdf->transformation_stack.dirty[M_PROJECTION] = true;
		transformation_stack_update(&fdf->transformation_stack);
		center_model(&fdf->transformation_stack, (float)fdf->width,
			(float)fdf->height, (float)(fdf->max_z - fdf->min_z));
	}
	return (0);
}

int	button_press_handler(int button, int x, int y, t_fdf *fdf)
{
	if (button == Button4)
		transformation_stack_zoom(&fdf->transformation_stack, -1);
	else if (button == Button5)
		transformation_stack_zoom(&fdf->transformation_stack, +1);
	else if (button == Button1 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_DRAGGING;
	}
	else if (button == Button3 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_ROTATING;
	}
	return (0);
}

int	button_release_handler(int button, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if ((button == Button1 || button == Button3)
		&& (fdf->input_state == INPUT_STATE_DRAGGING
			|| fdf->input_state == INPUT_STATE_ROTATING))
		fdf->input_state = INPUT_STATE_IDLE;
	return (0);
}

int	motion_handler(int x, int y, t_fdf *fdf)
{
	t_projection_ctl	*proj;
	float				ndcx;
	float				ndcy;

	ndcx = ((float) x - (float) fdf->drag_start[0]) / WINDOW_WIDTH;
	ndcy = ((float) fdf->drag_start[1] - (float) y) / WINDOW_HEIGHT;
	proj = &fdf->transformation_stack.projection;
	if (fdf->input_state == INPUT_STATE_DRAGGING)
	{
		transformation_stack_pan(&fdf->transformation_stack,
			ndcx * (proj->l - proj->r), ndcy * (proj->b - proj->t));
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	else if (fdf->input_state == INPUT_STATE_ROTATING)
	{
		transformation_stack_rotate_x(&fdf->transformation_stack,
			ndcy * (proj->b - proj->t) * ROTATE_FACTOR);
		transformation_stack_rotate_y(&fdf->transformation_stack,
			ndcx * (proj->r - proj->l) * ROTATE_FACTOR);
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	return (0);
}
