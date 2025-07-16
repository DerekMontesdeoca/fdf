/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_perspective.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:11:49 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 16:11:50 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void transformation_stack_persp_x(t_transformation_stack *t, float dx)
{
    t->dirty[M_PERSPECTIVE_X] = true;
    t->px += dx;
}

void transformation_stack_persp_y(t_transformation_stack *t, float dy)
{
    t->dirty[M_PERSPECTIVE_Y] = true;
    t->py += dy;
}

void transformation_stack_persp_z(t_transformation_stack *t, float dz)
{

    t->dirty[M_PERSPECTIVE_Z] = true;
    t->pz += dz;
}