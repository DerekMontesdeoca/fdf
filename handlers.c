/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:02:13 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 16:02:14 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "mlx/mlx.h"
#include "fdf.h"

int	key_press_handler(const int keycode, void *mlx)
{
    if (keycode == XK_Escape)
        mlx_loop_end(mlx);
    return (0);
}

int button_press_handler(int button, int x, int y, t_fdf *fdf)
{
    (void) x, (void) y;
    if (button == Button4)
        transformation_stack_scale(&fdf->transformation_stack, 0.5f);
    else if (button == Button5)
        transformation_stack_scale(&fdf->transformation_stack, -0.5f);
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

int button_release_handler(int button, int x, int y, t_fdf *fdf)
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
    if (fdf->input_state == INPUT_STATE_DRAGGING)
    {
        transformation_stack_translate(&fdf->transformation_stack,
            (float)(x - fdf->drag_start[0]), (float)(y - fdf->drag_start[1]), 0);
        fdf->drag_start[0] = x;
        fdf->drag_start[1] = y;
    }
    else if (fdf->input_state == INPUT_STATE_ROTATING)
    {
        transformation_stack_rotate_x(&fdf->transformation_stack,
            (float)(y - fdf->drag_start[1]) * -0.004f);
        transformation_stack_rotate_y(&fdf->transformation_stack,
            (float)(x - fdf->drag_start[0]) * 0.04f);
        fdf->drag_start[0] = x;
        fdf->drag_start[1] = y;
    }
    return (0);
}
