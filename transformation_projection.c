/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_projection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:11:49 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 16:11:50 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"
#define ISOMETRIC_ANGLE 0.6155f

void	transformation_stack_isometric(t_transformation_stack *t)
{
	(void) t;
	transformation_stack_rview_z(t, M_PI_4);
	transformation_stack_rview_x(t, M_PI_2);
	transformation_stack_rview_x2(t, -ISOMETRIC_ANGLE);
}

void	transformation_stack_parallel(t_transformation_stack *t)
{
	(void) t;
}
