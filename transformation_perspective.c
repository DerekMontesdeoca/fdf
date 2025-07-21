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

void	transformation_stack_ortho(
	t_transformation_stack *t,
	float x,
	float y,
	float z
) {
	t->dirty[M_PROJECTION] = true;
	t->projection.type = PROJECTION_ORTHO;
	t->projection.box[0] = x;
	t->projection.box[1] = y;
	t->projection.box[2] = z;
}
