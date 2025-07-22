/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:42:54 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/20 01:42:58 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mlx.h>
#include <X11/X.h>
#include "libft/libft.h"

static inline void	init_transformation_stack(t_fdf *f)
{
	t_projection_ctl *projection;

	f->transformation_stack.dirty[M_PROJECTION] = true;
	projection = &f->transformation_stack.projection;
	projection->type = PROJECTION_ORTHO;
	transformation_stack_origin(&f->transformation_stack,
		-((float)f->width / 2), -((float)f->height / 2),
		-(float)(f->min_z + f->max_z) / 2.0f);
	transformation_stack_isometric(&f->transformation_stack);
	make_projection_ctl(projection, f->width, f->height, f->max_z - f->min_z);
	transformation_stack_translate(&f->transformation_stack, 0, 0,
		-projection->box[2] / 2.0f);
	transformation_stack_update(&f->transformation_stack);
	// center_model(&f->transformation_stack, (float)(f->max_z - f->min_z));
}

static inline void	init_mlx_handlers(t_fdf *f)
{
	mlx_hook(f->window, Expose, ExposureMask, fdf_render, f);
	mlx_hook(f->window, DestroyNotify, SubstructureNotifyMask, mlx_loop_end,
		f->mlx);
	mlx_loop_hook(f->mlx, fdf_render, f);
	mlx_hook(f->window, KeyPress, KeyPressMask, key_press_handler, f->mlx);
	mlx_hook(f->window, ButtonPress, ButtonPressMask, button_press_handler, f);
	mlx_hook(f->window, MotionNotify, Button1MotionMask | Button3MotionMask,
		motion_handler, f);
	mlx_hook(f->window, ButtonRelease, ButtonReleaseMask,
		button_release_handler, f);
}

static inline bool	init_after_parsing(t_fdf *f)
{
	bool	ok;
	size_t	n;

	ok = false;
	make_transformation_stack(&f->transformation_stack);
	init_transformation_stack(f);
	f->n_edges = (f->width - 1) * f->height
		+ (f->height - 1) * f->width;
	n = sizeof(int [f->n_edges][2]);
	f->edges = malloc(n);
	f->transformed_points = malloc(
			sizeof(t_point4[f->height * f->width]));
	if (f->edges != NULL && f->transformed_points != NULL)
	{
		fdf_init_edges(f);
		init_mlx_handlers(f);
		ok = true;
	}
	return (ok);
}

bool	make_fdf(t_fdf *f, char *filename)
{
	bool	ok;

	ok = false;
	f->mlx = mlx_init();
	if (f->mlx != NULL)
	{
		f->window = mlx_new_window(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
		f->image = mlx_new_image(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		ft_strlcpy(f->renderer.fps_string, "Fps:     ",
			sizeof(f->renderer.fps_string));
		f->renderer.data = mlx_get_data_addr(f->image, &f->renderer.bpp,
				&f->renderer.size_line, &f->renderer.is_big_endian);
		if (clock_gettime(CLOCK_MONOTONIC, &f->renderer.last_tick) == 0)
		{
			f->renderer.text_tick = f->renderer.last_tick;
			if (parse_file(f, filename)
				&& f->window != NULL
				&& f->image != NULL
				&& f->renderer.data != NULL)
				ok = init_after_parsing(f);
		}
		else
			perror("gettime: ");
	}
	return (ok);
}

void	fdf_destroy_contents(t_fdf *f)
{
	free(f->points);
	free(f->color);
	free(f->transformed_points);
	free(f->edges);
	mlx_destroy_image(f->mlx, f->image);
	mlx_destroy_window(f->mlx, f->window);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
}
