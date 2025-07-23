/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_projection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:11:49 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 12:35:20 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"
#define ISOMETRIC_ANGLE 0.6155f

void	transformation_stack_isometric(t_transformation_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	transformation_stack_rview_z(t, M_PI_4);
	transformation_stack_rview_x(t, M_PI_2);
	transformation_stack_rview_x2(t, -ISOMETRIC_ANGLE);
	transformation_stack_rotate_x(t, 0);
	transformation_stack_rotate_y(t, 0);
	transformation_stack_rotate_z(t, 0);
}

void	transformation_stack_parallel(t_transformation_stack *t)
{
	t->px = 0;
	t->px2 = 0;
	t->pz = 0;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	transformation_stack_rview_z(t, 0);
	transformation_stack_rview_x(t, 0);
	transformation_stack_rview_x2(t, 0);
	transformation_stack_rotate_x(t, 0);
	transformation_stack_rotate_y(t, 0);
	transformation_stack_rotate_z(t, 0);
}
