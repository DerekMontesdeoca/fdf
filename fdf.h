/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:51:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/13 08:48:21 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdbool.h>

typedef struct s_point3
{
	float	x;
	float	y;
	float	z; 
	float	pad;
}	t_point3;

void	identity_matrix4(float *out);
void	matrix4_multiply(const float *a, const float *b, float *out);
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

typedef enum e_matrices
{
	M_TB,
	M_ROTATION_Z,
	M_ROTATION_X,
	M_ROTATION_Y,
	M_SCALE,
	M_PERSPECTIVE_Y,
	M_PERSPECTIVE_X,
	M_PERSPECTIVE_Z,
	M_ORIGIN,
	M_COUNT
}	t_matrices;

typedef struct s_transformation_stack2
{
	float				matrices[M_COUNT][16];
	float				results[M_COUNT][16];
	float				temp[16];
	float				combined[16];
	bool				dirty[M_COUNT];
	float				px;
	float				py;
	float				pz;
	float				rx;
	float				ry;
	float				rz;
	float				scale;
	float				tx;
	float				ty;
	float				tz;
	float				ox;
	float				oy;
	float				oz;
}	t_transformation_stack;

void	make_transformation_stack(t_transformation_stack *t);
void	transformation_stack_translate(t_transformation_stack *t, float dx, float dy, float dz);
void	transformation_stack_origin(t_transformation_stack *t, float dx, float dy, float dz);
void	transformation_stack_scale(t_transformation_stack *t, float delta);
void	transformation_stack_rotate_x(t_transformation_stack *t, float dx);
void	transformation_stack_rotate_y(t_transformation_stack *t, float dy);
void	transformation_stack_rotate_z(t_transformation_stack *t, float dz);
void	transformation_stack_persp_x(t_transformation_stack *t, float dx);
void	transformation_stack_persp_y(t_transformation_stack *t, float dy);
void	transformation_stack_persp_z(t_transformation_stack *t, float dz);
void	transformation_stack_update(t_transformation_stack *t);

typedef enum e_axis_major
{
	X_MAJOR,
	Y_MAJOR,
}	t_axis_major;

typedef struct s_bresenham_state
{
	int				delta[3];
	int				step[3];
	t_axis_major 	axis_major;
	int 			error_count;
}	t_bresenham_state;

typedef struct s_renderer
{
	char *data;
	int	bpp;
	int	size_line;
	int	is_big_endian;
}	t_renderer;

typedef enum e_input_state
{
	INPUT_STATE_IDLE,
	INPUT_STATE_DRAGGING,
	INPUT_STATE_ROTATING,
}	t_input_state;

typedef struct s_fdf
{
	t_point3				*points;
	t_point3				*transformed_points;
	int						(*edges)[2];
	int						width;
	int						height;
	size_t					n_edges;
	void					*mlx;
	void					*window;
	void					*image;
	t_renderer				renderer;
	t_bresenham_state 		bresenham_state;
	t_transformation_stack	transformation_stack;
	t_input_state			input_state;
	int						drag_start[2];
}	t_fdf;

void	make_fdf(t_fdf *f);
int		fdf_render(t_fdf *f);

#endif
