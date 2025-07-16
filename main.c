/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:45:31 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/14 00:38:25 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx/mlx.h>
#include <math.h>
#include <X11/X.h>
#include "libft/libft.h"
#include "fdf.h"

#define ISO_X_ROTATION_RADS 0.61547970867038734106

static inline int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void transform_points(t_fdf *f)
{
	size_t	i;
	size_t	j;
	size_t	k;
	float	*sp;
	float	*dp;

	i = 0;
	while ((int)i < f->width * f->height)
	{
		f->points[i].pad = 1; // Important to enable translation.
		sp = (float *) &f->points[i];
		dp = (float *) &f->transformed_points[i];
		j = 0;
		while (j < 4)
		{
			dp[j] = 0;
			k = 0;
			while (k < 4)
			{
				dp[j] += f->transformation_stack.combined[j * 4 + k] * sp[k];
				++k;
			}
			++j;
		}
		++i;
	}
}

void	clear_screen(t_fdf *f)
{
	size_t	i;

	i = 0;
	while (i < 600 * 600)
	{
		((unsigned int*)f->renderer.data)[i] = 0x00101010;
		++i;
	}
}

void draw_line_x_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	int	x;
	int	y;
	int j;

	bresenham->error_count = 2 * bresenham->delta[1] - bresenham->delta[0];
	x = bresenham->p1[0];
	y = bresenham->p1[1];
	j = 0;
	while (j <= bresenham->delta[0])
	{
		if (x >= 0 && x < 600 && y >= 0 && y < 600)
			screen[y * 600 + x] = 0xffffffff;
		x += bresenham->step[0];
		bresenham->error_count += 2 * bresenham->delta[1];
		if (bresenham->error_count > 0)
		{
			y += bresenham->step[1];
			bresenham->error_count -= 2 * bresenham->delta[0];
		}
		++j;
	}
}

void draw_line_y_major(t_bresenham_state *bresenham, unsigned int *screen)
{
	int	x;
	int	y;
	int i;

	bresenham->error_count = 2 * bresenham->delta[1] - bresenham->delta[0];
	x = bresenham->p1[0];
	y = bresenham->p1[1];
	i = 0;
	while (i <= bresenham->delta[1])
	{
		if (x >= 0 && x < 600 && y >= 0 && y < 600)
			screen[y * 600 + x] = 0xffffffff;
		y += bresenham->step[1];
		bresenham->error_count += 2 * bresenham->delta[0];
		if (bresenham->error_count > 0)
		{
			x += bresenham->step[0];
			bresenham->error_count -= 2 * bresenham->delta[1];
		}
		++i;
	}
}

void bresenham_init(t_bresenham_state *b, t_point3 *p1, t_point3 *p2)
{
	b->p1[0] = (int)p1->x;
	b->p1[1] = (int)p1->y;
	b->p1[2] = (int)p1->z;
	b->p2[0] = (int)p2->x;
	b->p2[1] = (int)p2->y;
	b->p2[2] = (int)p2->z;
	b->delta[0] = b->p2[0] - b->p1[0];
	b->delta[1] = b->p2[1] - b->p1[1];
	b->delta[2] = b->p2[2] - b->p1[2];
	b->step[0] = 1;
	b->step[1] = 1;
	if (b->delta[0] < 0)
		b->step[0] = -1;
	if (b->delta[1] < 0)
		b->step[1] = -1;
	b->delta[0] = ft_abs(b->p2[0] - b->p1[0]);
	b->delta[1] = ft_abs(b->p2[1] - b->p1[1]);
	b->delta[2] = ft_abs(b->p2[2] - b->p1[2]);
}

int	fdf_render(t_fdf *f)
{
	size_t	i;

	transformation_stack_update(&f->transformation_stack);
	transform_points(f);
	clear_screen(f);
	i = 0;
	while (i < f->n_edges)
	{
		bresenham_init(&f->bresenham_state,
			&f->transformed_points[f->edges[i][0]],
			&f->transformed_points[f->edges[i][1]]);
		if (f->bresenham_state.delta[0] >= f->bresenham_state.delta[1])
			draw_line_x_major(&f->bresenham_state, (unsigned int *)f->renderer.data);
		else
			draw_line_y_major(&f->bresenham_state, (unsigned int *)f->renderer.data);
		++i;
	}
	if (mlx_put_image_to_window(f->mlx, f->window, f->image, 0, 0) == -1)
		return (-1);
	return (0);
}

int main()
{
	t_fdf fdf = (t_fdf){0};

	fdf.mlx = mlx_init();
	if (fdf.mlx != NULL)
	{
		fdf.window = mlx_new_window(fdf.mlx, 600, 600, "FDF");
		fdf.image = mlx_new_image(fdf.mlx, 600, 600);
		fdf.renderer.data = mlx_get_data_addr( fdf.image,
			&fdf.renderer.bpp,
			&fdf.renderer.size_line,
			&fdf.renderer.is_big_endian);
		if (parse_file(&fdf) 
				&& fdf.window != NULL
				&& fdf.image != NULL 
				&& fdf.renderer.data != NULL
		) {
			make_transformation_stack(&fdf.transformation_stack);
			transformation_stack_persp_x(&fdf.transformation_stack, ISO_X_ROTATION_RADS);
			transformation_stack_persp_z(&fdf.transformation_stack, (float)M_PI/4.0f);
			transformation_stack_origin(&fdf.transformation_stack,
			-((float)fdf.width / 2), -((float)fdf.height / 2), -5.0f);
			transformation_stack_translate(&fdf.transformation_stack,
				300, 300, 0);
			transformation_stack_scale(&fdf.transformation_stack, 10);

			fdf.n_edges = (fdf.width - 1) * fdf.height
				+ (fdf.height - 1) * fdf.width;
			fdf.edges = malloc(sizeof(int[fdf.n_edges][2]));
			fdf.transformed_points = malloc(
					sizeof(t_point3[fdf.height * fdf.width]));
			if (fdf.edges != NULL && fdf.transformed_points != NULL)
			{
				int y = 0;
				int x = 0;
				size_t i = 0;
				while (y < fdf.height)
				{
					x = 0;
					while (x < fdf.width - 1)
					{
						fdf.edges[i][0] = y * fdf.width + x;
						fdf.edges[i][1] = y * fdf.width + x + 1;
						++x;
						++i;
					}
					++y;
				}
				y = 0;
				while (y < fdf.height - 1)
				{
					x = 0;
					while (x < fdf.width)
					{
						fdf.edges[i][0] = y * fdf.width + x;
						fdf.edges[i][1] = (y + 1) * fdf.width + x;
						++x;
						++i;
					}
					++y;
				}
				mlx_loop_hook(fdf.mlx, fdf_render, &fdf);
				mlx_hook(fdf.window, Expose, ExposureMask, fdf_render , &fdf);
				mlx_hook(fdf.window, KeyPress, KeyPressMask, key_press_handler, fdf.mlx);
				mlx_hook(fdf.window, ButtonPress, ButtonPressMask, button_press_handler, &fdf);
				mlx_hook(fdf.window, ButtonRelease, ButtonReleaseMask, button_release_handler, &fdf);
				mlx_hook(fdf.window, MotionNotify, Button1MotionMask | Button3MotionMask, motion_handler, &fdf);
				mlx_hook(fdf.window, DestroyNotify, SubstructureNotifyMask, mlx_loop_end, fdf.mlx);
				mlx_loop(fdf.mlx);
			}
		}
		free(fdf.points);
		free(fdf.edges);
		free(fdf.transformed_points);
		mlx_destroy_image(fdf.mlx, fdf.image);
		mlx_destroy_window(fdf.mlx, fdf.window);
		mlx_destroy_display(fdf.mlx);
		free(fdf.mlx);
	}
	return (EXIT_SUCCESS);
}
