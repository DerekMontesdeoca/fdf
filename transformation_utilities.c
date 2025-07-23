/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 05:46:17 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 13:18:28 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include "libft/libft.h"

void	center_model(
	t_transformation_stack *t,
	float width,
	float height,
	float depth
) {
	float	vec[4];
	float	result[4];

	vec[0] = width / 2;
	vec[1] = height / 2;
	vec[2] = depth / 2;
	vec[3] = 1;
	matrix4_dot_product(t->combined, vec, result);
	transformation_stack_pan(t, 0,
		-result[1] * t->projection.box[1] / 2);
}
