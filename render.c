/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:45:37 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/20 01:45:41 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <immintrin.h>
#include <stdint.h>
#include <time.h>
#include <mlx/mlx.h>
#include <stdbool.h>
#include "fdf.h"
#include "libft/libft.h"

void	transform_points(t_fdf *f)
{
	int		i[3];
	float	*sp;
	float	*dp;

	i[0] = 0;
	while ((int)i[0] < f->width * f->height)
	{
		f->points[i[0]].w = 1;
		sp = (float *) &f->points[i[0]];
		dp = (float *) &f->transformed_points[i[0]];
		i[1] = 0;
		while (i[1] < 4)
		{
			dp[i[1]] = 0;
			i[2] = 0;
			while (i[2] < 4)
			{
				dp[i[1]] += f->transformation_stack.combined[i[1] * 4 + i[2]]
					* sp[i[2]];
				++i[2];
			}
			++i[1];
		}
		++i[0];
	}
}

#ifdef AVX

void	clear_screen(t_fdf *f)
{
	__m256i		vec;
	uint32_t	value;
	int			i;

	i = 0;
	value = 0x00101010;
	while (i < WINDOW_HEIGHT * WINDOW_WIDTH
		&& ((uintptr_t)(((uint32_t *)f->renderer.data) + i) & (1 << 5) - 1))
	{
		((uint32_t *)f->renderer.data)[i] = value;
		++i;
	}
	vec = _mm256_set1_epi32((int)value);
	while (i + 8 <= WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		_mm256_stream_si256((__m256i *)(((uint32_t *) f->renderer.data) + i),
			vec);
		i += 8;
	}
	while (i < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		((uint32_t *)f->renderer.data)[i] = value;
		++i;
	}
	_mm_sfence();
}

#else

void	clear_screen(t_fdf *f)
{
	size_t	i;

	i = 0;
	while (i < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		((unsigned int *)f->renderer.data)[i] = (unsigned int)0x00101010;
		++i;
	}
}

#endif

int	fdf_render(t_fdf *f)
{
	if (clock_gettime(CLOCK_MONOTONIC, &f->renderer.tick) < 0)
		return (-1);
	transformation_stack_rotate_y(&f->transformation_stack, 0.00001f);
	transformation_stack_update(&f->transformation_stack);
	transform_points(f);
	update_timer(&f->renderer);
	clear_screen(f);
	draw_lines(f);
	render_string(f->renderer.fps_string, (uint32_t *) f->renderer.data, 100,
		100);
	if (mlx_put_image_to_window(f->mlx, f->window, f->image, 0, 0) == -1)
		return (-1);
	return (0);
}
