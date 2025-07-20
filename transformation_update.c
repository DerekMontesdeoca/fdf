/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_update.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:13:44 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 16:13:45 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stddef.h>
#include "fdf.h"
#include "libft/libft.h"

static inline void	update_rotations(t_transformation_stack *t)
{
	if (t->dirty[M_VIEW_ROTATE_X])
		matrix4_rotate_x_abs(t->results[M_VIEW_ROTATE_X], t->px);
	if (t->dirty[M_VIEW_ROTATE_Y])
		matrix4_rotate_y_abs(t->results[M_VIEW_ROTATE_Y], t->py);
	if (t->dirty[M_VIEW_ROTATE_Z])
		matrix4_rotate_z_abs(t->results[M_VIEW_ROTATE_Z], t->pz);
	if (t->dirty[M_ROTATION_X])
		matrix4_rotate_x_abs(t->results[M_ROTATION_X], t->rx);
	if (t->dirty[M_ROTATION_Y])
		matrix4_rotate_y_abs(t->results[M_ROTATION_Y], t->ry);
	if (t->dirty[M_ROTATION_Z])
		matrix4_rotate_x_abs(t->results[M_ROTATION_Z], t->rz);
}

static inline void	update_translation(t_transformation_stack *t)
{
	if (t->dirty[M_TB])
	{
		t->results[M_TB][3] = t->tx;
		t->results[M_TB][7] = t->ty;
		t->results[M_TB][11] = t->tz;
	}
	if (t->dirty[M_ORIGIN])
	{
		t->results[M_ORIGIN][3] = t->ox;
		t->results[M_ORIGIN][7] = t->oy;
		t->results[M_ORIGIN][11] = t->oz;
	}
}

static inline void	recompute_final_transformation(t_transformation_stack *t)
{
	float	*pingpong[2];
	size_t	i;

	pingpong[0] = t->temp;
	pingpong[1] = t->combined;
	if (M_COUNT & 1)
	{
		pingpong[0] = t->combined;
		pingpong[1] = t->temp;
	}
	ft_memcpy(pingpong[0], t->results[0], sizeof(float [16]));
	i = 0;
	while (i < M_COUNT - 1)
	{
		matrix4_multiply(pingpong[i & 1], t->results[i + 1],
			pingpong[!(i & 1)]);
		++i;
	}
	ft_memset(t->dirty, 0, sizeof(t->dirty));
}

void	transformation_stack_update(t_transformation_stack *t)
{
	bool	should_update;
	size_t	i;

	update_rotations(t);
	update_translation(t);
	transformation_update_projection(t);
	should_update = false;
	i = 0;
	while (i < M_COUNT)
	{
		should_update |= t->dirty[i];
		t->dirty[i] = false;
		++i;
	}
	if (should_update)
		recompute_final_transformation(t);
}
