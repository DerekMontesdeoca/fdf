/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_rotation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:06:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 16:11:01 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transformation_stack_rotate_x(t_transformation_stack *t, float dx)
{
	t->dirty[M_ROTATION_X] = true;
	t->rx += dx;
}

void	transformation_stack_rotate_y(t_transformation_stack *t, float dy)
{
	t->dirty[M_ROTATION_Y] = true;
	t->ry += dy;
}

void	transformation_stack_rotate_z(t_transformation_stack *t, float dz)
{
	t->dirty[M_ROTATION_Z] = true;
	t->rz += dz;
}
