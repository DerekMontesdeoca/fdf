/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:51:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/11 20:01:39 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdbool.h>
#include <stddef.h>

typedef struct s_point3
{
	float	x;
	float	y;
	float	z; 
	float	pad;
}	t_point3;

void	identity_matrix4(float *out);
void	matrix4_multiply(float *a, float *b, float *out);
void	matrix4_scalar_multiply(float *m, float scalar);
void	matrix4_rotate_x_abs(float *m, float rads);
void	matrix4_rotate_y_abs(float *m, float rads);
void	matrix4_rotate_z_abs(float *m, float rads);
void	matrix4_translate(
			float *m,
			float delta_x,
			float delta_y,
			float delta_z
			);

typedef struct s_rotation_matrix
{
	float	x[16];
	float	y[16];
	float	z[16];
	float	combined[16];
}	t_rotation_matrix;

void	make_rotation_matrix(t_rotation_matrix *r);
void	rotation_matrix_combine(t_rotation_matrix *r);

typedef struct s_transformation_stack
{
	float				origin[16];
	float				scale[16];
	t_rotation_matrix	rotation;
	float				tb[16];
	float				perspective[16];
	float				combined[16];
}	t_transformation_stack;

/**
 * Initialize all matrices to their identity.
 */
void	make_transformation_stack(t_transformation_stack *t);

/**
 * Caches the result of multiplying the transformation stack.
 */
void	transformation_stack_combine(t_transformation_stack *t);

typedef struct s_bresenham_state
{
	int something;
}	t_bresenham_state;

bool	draw_line(
			t_bresenham_state *state,
			t_point3 *p0,
			t_point3 *p1,
			bool (*draw_func)(int x, int y)
			);

typedef struct s_fdf
{
	void		*arena;
	t_point3	*points;
	t_point3	*transformed_points;
	int			(*edges)[2];
	size_t		size;
}	t_fdf;

void	make_fdf(t_fdf *f);

#endif
