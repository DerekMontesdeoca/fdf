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
#include <stdbool.h>
#include <unistd.h>
#include <mlx/mlx.h>
#include <math.h>
#include <X11/X.h>
#include "fdf.h"
#include "libft/libft.h"
#include "mlx/mlx_int.h"

#define INPUT_BUF_SIZE 4096
#define CUTOFF 214748364
#define ISO_X_ROTATION_RADS 0.61547970867038734106

void	make_transformation_stack(t_transformation_stack *t)
{
	size_t	i;

	t->scale = 1;
	t->rx = 0;
	t->ry = 0;
	t->rz = 0;
	t->ox = 0;
	t->oy = 0;
	t->oz = 0;
	t->px = 0;
	t->tx = 0;
	t->ty = 0;
	t->tz = 0;
	i = 0;
	while (i < M_COUNT)
	{
		t->dirty[i] = true;
		identity_matrix4(t->matrices[i]);
		identity_matrix4(t->results[i]);
		++i;
	}
}

void transformation_stack_translate(t_transformation_stack *t, float dx, float dy, float dz)
{
	t->dirty[M_TB] = true;
	t->tx += dx;
	t->ty += dy;
	t->tz += dz;
}

void transformation_stack_scale(t_transformation_stack *t, float delta)
{
	t->dirty[M_SCALE] = true;
	t->scale += delta;
}

void transformation_stack_rotate_x(t_transformation_stack *t, float dx)
{
	t->dirty[M_ROTATION_X] = true;
	t->rx += dx;
}

void transformation_stack_rotate_y(t_transformation_stack *t, float dy)
{
	t->dirty[M_ROTATION_Y] = true;
	t->ry += dy;
}

void transformation_stack_rotate_z(t_transformation_stack *t, float dz)
{
	t->dirty[M_ROTATION_Z] = true;
	t->rz += dz;
}

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

void transformation_stack_origin(t_transformation_stack *t, float dx, float dy, float dz)
{
	t->dirty[M_ORIGIN] = true;
	t->ox += dx;
	t->oy += dy;
	t->oz += dz;
}

void identity_matrix4(float *out)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		out[i * 4 + i] = 1;
		++i;
	}
}

void matrix4_rotate_x_abs(float *m, float rads)
{
	m[5] = cosf(rads);
	m[6] = -sinf(rads);
	m[9] = sinf(rads);
	m[10] = cosf(rads);
}

void matrix4_rotate_y_abs(float *m, float rads)
{
	m[0] = cosf(rads);
	m[2] = sinf(rads);
	m[8] = -sinf(rads);
	m[10] = cosf(rads);
}

void matrix4_rotate_z_abs(float *m, float rads)
{
	m[0] = cosf(rads);
	m[1] = -sinf(rads);
	m[4] = sinf(rads);
	m[5] = cosf(rads);
}

int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	matrix4_multiply(const float *a, const float *b, float *out)
{
	int	i;
	int	j;
	int	k;

	ft_memset(out, 0, sizeof(float[16]));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				out[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
				++k;
			}
			++j;
		}
		++i;
	}
}

static inline bool is_delim(char c)
{
	return (c == ' ' || c == '\n');
}

bool	strntoi(int *n, char *str, size_t len, size_t *last)
{
	size_t			i;
	bool			is_negative;
	unsigned int	nlim;
	unsigned int	accumulator;

	accumulator = 0;
	i = 0;
	while (i <= len && is_delim(str[i]))
		++i;
	is_negative = false;
	if (i <= len && (str[i] == '+' || str[i] == '-'))
	{
		is_negative = str[i] == '-';
		++i;
	}
	nlim = 7;
	if (is_negative)
		nlim = 8;
	if (!ft_isdigit(str[i])) 
		return (false);
	while (i <= len && ft_isdigit(str[i]))
	{
		if (accumulator > CUTOFF || 
				(accumulator == CUTOFF &&
				(unsigned int)(str[i] - '0') > nlim))
			return (false);
		accumulator = accumulator * 10 + (str[i] - '0');
		++i;
	}
	if (is_negative)
		*n = (int)-accumulator;
	else
		*n = (int)accumulator;
	*last = i;
	return (true);
}

bool	parse_file_inner(t_fdf *fdf, int fd, char *buf)
{
	ssize_t			bytes_read;
	size_t			values_read;
	size_t			read_start;
	size_t			last_delim;
	size_t			i;
	size_t			arr_capacity;
	t_point3		*temp;
	int				x;
	int				y;
	int				z;
	bool			width_set;
	bool			delim_found;
	size_t			last;

	x = 0;
	y = 0;
	width_set = false;

	if (buf == NULL)
		return (false);

	arr_capacity = 0;
	values_read = 0;
	read_start = 0;

	while (true)
	{
		bytes_read = read(fd, buf + read_start, INPUT_BUF_SIZE - read_start);
		if (bytes_read < 0)
			return (false);

		// Find the last delim of the buffer read.
		last_delim = read_start + bytes_read;
		delim_found = false;
		while (last_delim-- > 0)
		{
			if (is_delim(buf[last_delim]))
			{
				delim_found = true;
				break;
			}
		}

		if (!delim_found && read_start + bytes_read >= INPUT_BUF_SIZE)
		{
			ft_fprintf(STDERR_FILENO, "Error: 1 file input value too long");
			return (false);
		}
		if (delim_found || (bytes_read == 0 && read_start != 0))
		{
			i = 0;
			while (true)
			{
				while (i < read_start + bytes_read && is_delim(buf[i]))
					++i;
				if (i >= last_delim)
					break;
				if (!strntoi(&z, &buf[i], last_delim - i, &last))
					return (false);
				i += last;
				while (i < read_start + bytes_read && buf[i] == ' ')
					++i;

				// Resize Vector
				if (values_read >= arr_capacity)
				{
					if (arr_capacity == 0)
						arr_capacity = 4096;
					else
						arr_capacity *= 2;
					temp = malloc(sizeof(t_point3[arr_capacity]));
					if (temp == NULL)
						return (false);
					ft_memcpy(temp, fdf->points, sizeof(t_point3[values_read]));
					free(fdf->points);
					fdf->points = temp;
				}

				fdf->points[values_read].x = (float)x;
				fdf->points[values_read].y = (float)y;
				fdf->points[values_read].z = (float)z;
				++values_read;
				++x;

				// Advance row
				if (i < read_start + bytes_read && (bytes_read == 0 || buf[i] == '\n'))
				{
					x = 0;
					++y;
					++fdf->height;
					if (!width_set)
					{
						width_set = true;
						fdf->width = values_read;
					} 
					else
					{
						if ((size_t)y * fdf->width + x != values_read)
						{
							ft_fprintf(STDERR_FILENO, "Error: Rows of different"
									" sizes not allowed");
							return (false);
						}
					}
				}
			}
			if (bytes_read == 0)
				break;
			// copy rest after last delimitter
			ft_memmove(buf, &buf[last_delim+1], read_start + bytes_read - last_delim - 1);
			read_start = read_start + bytes_read - last_delim - 1;
		}
		else
			break;
	}
	return (true);
}

bool	parse_file(t_fdf *fdf)
{
	char	*buf;
	bool	ok;

	buf = malloc(INPUT_BUF_SIZE);
	if (buf == NULL)
		return (false);
	ok = parse_file_inner(fdf, STDIN_FILENO, buf);
	free(buf);
	return (ok);
}

void	transformation_stack_update(t_transformation_stack *t)
{
	bool	should_update;
	size_t	i;

	if (t->dirty[M_SCALE])
	{
		t->results[M_SCALE][0] = t->scale * t->matrices[M_SCALE][0];
		t->results[M_SCALE][5] = t->scale * t->matrices[M_SCALE][5];
		t->results[M_SCALE][10] = t->scale * t->matrices[M_SCALE][10];
	}
	if (t->dirty[M_PERSPECTIVE_X])
		matrix4_rotate_x_abs(t->results[M_PERSPECTIVE_X], t->px);
	if (t->dirty[M_PERSPECTIVE_Y])
		matrix4_rotate_y_abs(t->results[M_PERSPECTIVE_Y], t->py);
	if (t->dirty[M_PERSPECTIVE_Z])
		matrix4_rotate_z_abs(t->results[M_PERSPECTIVE_Z], t->pz);
	if (t->dirty[M_ROTATION_X])
		matrix4_rotate_x_abs(t->results[M_ROTATION_X], t->rx);
	if (t->dirty[M_ROTATION_Y])
		matrix4_rotate_y_abs(t->results[M_ROTATION_Y], t->ry);
	if (t->dirty[M_ROTATION_Z])
		matrix4_rotate_x_abs(t->results[M_ROTATION_Z], t->rz);
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
	should_update = false;
	i = 0;
	while (i < M_COUNT)
	{
		if (t->dirty[i])
		{
			should_update = true;
			break;
		}
		++i;
	}
	if (should_update)
	{
		float *pingpong[2];
		pingpong[0] = t->temp;
		pingpong[1] = t->combined;
		if (M_COUNT & 1)
		{
			pingpong[0] = t->combined;
			pingpong[1] = t->temp;
		}
		ft_memcpy(pingpong[0], t->results[0], sizeof(float[16]));
		i = 0;
		while (i < M_COUNT - 1)
		{
			matrix4_multiply(pingpong[i & 1], t->results[i + 1], pingpong[!(i & 1)]);
			++i;
		}
		ft_memset(t->dirty, 0, sizeof(t->dirty));
	}
}

int	fdf_render(t_fdf *f)
{
	size_t	i;
	size_t	j;
	size_t	k;
	float		*sp;
	float		*dp;

	// Update matrices
	transformation_stack_update(&f->transformation_stack);

	// Transform points
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

	int i1 = 0;
	while (i1 < 600 * 600)
	{
		((unsigned int*)f->renderer.data)[i1] = 0x00101010;
		++i1;
	}

	int x;
	int y;
	int p1[3];
	int p2[3];
	int *d;
	i = 0;
	while (i < f->n_edges)
	{
		p1[0] = (int)f->transformed_points[f->edges[i][0]].x;
		p1[1] = (int)f->transformed_points[f->edges[i][0]].y;
		p1[2] = (int)f->transformed_points[f->edges[i][0]].z;

		p2[0] = (int)f->transformed_points[f->edges[i][1]].x;
		p2[1] = (int)f->transformed_points[f->edges[i][1]].y;
		p2[2] = (int)f->transformed_points[f->edges[i][1]].z;

		d = f->bresenham_state.delta;
		d[0] = p2[0] - p1[0];
		d[1] = p2[1] - p1[1];
		d[3] = p2[2] - p1[2];
		f->bresenham_state.step[0] = 1;
		f->bresenham_state.step[1] = 1;
		if (d[0] < 0)
			f->bresenham_state.step[0] = -1;
		if (d[1] < 0)
			f->bresenham_state.step[1] = -1;
		d[0] = ft_abs(p2[0] - p1[0]);
		d[1] = ft_abs(p2[1] - p1[1]);
		d[2] = ft_abs(p2[2] - p1[2]);

		if (d[0] >= d[1])
		{
			// X major
			f->bresenham_state.axis_major = X_MAJOR;
			f->bresenham_state.error_count = 2 * d[1] - d[0];
			x = p1[0];
			y = p1[1];
			j = 0;
			while ((int)j <= d[0])
			{
				if (x >= 0 && x < 600 && y >= 0 && y < 600)
					((unsigned int*) f->renderer.data)[y * 600 + x] = 0xffffffff;
				x += f->bresenham_state.step[0];
				f->bresenham_state.error_count += 2 * d[1];
				if (f->bresenham_state.error_count > 0)
				{
					y += f->bresenham_state.step[1];
					f->bresenham_state.error_count -= 2 * d[0];
				}
				++j;
			}
		}
		else
		{
			// Y major
			f->bresenham_state.axis_major = Y_MAJOR;
			f->bresenham_state.error_count = 2 * d[0] - d[1];
			x = p1[0];
			y = p1[1];
			j = 0;
			while ((int)j <= d[1])
			{
				if (x >= 0 && x < 600 && y >= 0 && y < 600)
					((unsigned int*) f->renderer.data)[y * 600 + x] = 0xffffffff;
				y += f->bresenham_state.step[1];
				f->bresenham_state.error_count += 2 * d[0];
				if (f->bresenham_state.error_count > 0)
				{
					x += f->bresenham_state.step[0];
					f->bresenham_state.error_count -= 2 * d[1];
				}
				++j;
			}
		}
		++i;
	}
	if (mlx_put_image_to_window(f->mlx, f->window, f->image, 0, 0) == -1)
		return (-1);
	return (0);
}

int	key_press_handler(const int keycode, void *mlx)
{
	if (keycode == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
}

int button_press_handler(int button, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;

	if (button == Button4)
		transformation_stack_scale(&fdf->transformation_stack, 0.5f);
	else if (button == Button5)
		transformation_stack_scale(&fdf->transformation_stack, -0.5f);
	else if (button == Button1 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_DRAGGING;
	}
	else if (button == Button3 && fdf->input_state == INPUT_STATE_IDLE)
	{
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
		fdf->input_state = INPUT_STATE_ROTATING;
	}
	return (0);
}

int button_release_handler(int button, int x, int y, t_fdf *fdf)
{
	(void) x;
	(void) y;
	if ((button == Button1 || button == Button3)
		&& (fdf->input_state == INPUT_STATE_DRAGGING
			|| fdf->input_state == INPUT_STATE_ROTATING))
		fdf->input_state = INPUT_STATE_IDLE;
	return (0);
}

int	motion_handler(int x, int y, t_fdf *fdf)
{
	if (fdf->input_state == INPUT_STATE_DRAGGING)
	{
		transformation_stack_translate(&fdf->transformation_stack,
			(float)(x - fdf->drag_start[0]), (float)(y - fdf->drag_start[1]), 0);
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	else if (fdf->input_state == INPUT_STATE_ROTATING)
	{
		transformation_stack_rotate_x(&fdf->transformation_stack,
			(float)(y - fdf->drag_start[1]) * -0.007f);
		transformation_stack_rotate_y(&fdf->transformation_stack,
			(float)(x - fdf->drag_start[0]) * 0.04f);
		fdf->drag_start[0] = x;
		fdf->drag_start[1] = y;
	}
	return (0);
}

int main()
{
	t_fdf fdf = (t_fdf){0};

	fdf.mlx = mlx_init();
	if (fdf.mlx != NULL)
	{
		fdf.window = mlx_new_window(fdf.mlx, 600, 600, "My test");
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
		// TODO: Make sure that we can free these like that, do we zero
		// initialize everything?
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
