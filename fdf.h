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

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1920
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 1080
# endif

# if WINDOW_HEIGHT * WINDOW_WIDTH < 32
#  error "window height * window width must be greater than 32"
# endif

typedef struct s_draw_char_params
{
	uint32_t	*buf;
	uint32_t	color;
	int			x;
	int			y;
}	t_draw_char_params;

typedef struct s_parser
{
	char			*buf;
	ssize_t			bytes_read;
	size_t			values_read;
	size_t			arr_capacity;
	uint32_t		color;
	int				x;
	int				y;
	int				z;
	int				min_z;
	int				max_z;
	bool			z_set;
	bool			width_set;
	bool			has_color;
}	t_parser;

typedef struct s_point4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_point4;

typedef enum e_matrices
{
	M_PROJECTION,
	M_TB,
	M_ROTATION_Z,
	M_ROTATION_X,
	M_ROTATION_Y,
	M_VIEW_ROTATE_Y,
	M_VIEW_ROTATE_X,
	M_VIEW_ROTATE_Z,
	M_ORIGIN,
	M_COUNT,
}	t_matrices;

typedef enum e_projection
{
	PROJECTION_ORTHO,
	PERSPECTIVE_CONICAL,
}	t_projection;

typedef struct s_projection_ctl
{
	float			box[3];
	t_projection	type;
	float			fov;
	float			zoom_factor;
	float			pan_x;
	float			pan_y;
	float			l;
	float			r;
	float			t;
	float			b;
	float			f;
	float			n;
}	t_projection_ctl;

typedef struct s_transformation_stack
{
	float				matrices[M_COUNT][16];
	float				results[M_COUNT][16];
	float				temp[16];
	float				combined[16];
	bool				dirty[M_COUNT];
	t_projection_ctl	projection;
	float				px;
	float				py;
	float				pz;
	float				rx;
	float				ry;
	float				rz;
	float				tx;
	float				ty;
	float				tz;
	float				ox;
	float				oy;
	float				oz;
}	t_transformation_stack;

typedef struct s_bresenham_state
{
	int				delta[3];
	int				step[3];
	int				p1[3];
	int				p2[3];
	int				error_count;
	uint32_t		color1;
	uint32_t		color2;
	float			color_r_delta;
	float			color_g_delta;
	float			color_b_delta;
}	t_bresenham_state;

typedef struct s_renderer
{
	struct timespec	last_tick;
	struct timespec	tick;
	struct timespec	text_tick;
	struct timespec	temp;
	char			fps_string[10];
	int				fps;
	char			*data;
	int				bpp;
	int				size_line;
	int				is_big_endian;
}	t_renderer;

typedef enum e_input_state
{
	INPUT_STATE_IDLE,
	INPUT_STATE_DRAGGING,
	INPUT_STATE_ROTATING,
}	t_input_state;

typedef struct s_fdf
{
	uint32_t				*color;
	float					*points;
	t_point4				*transformed_points;
	int						(*edges)[2];
	int						width;
	int						height;
	int						min_z;
	int						max_z;
	size_t					n_edges;
	void					*mlx;
	void					*window;
	void					*image;
	t_renderer				renderer;
	t_bresenham_state		bresenham_state;
	t_transformation_stack	transformation_stack;
	t_input_state			input_state;
	int						drag_start[2];
	bool					has_color;
}	t_fdf;

/*
 * FDF
 */
bool	make_fdf(t_fdf *f, char *filename);
void	fdf_destroy_contents(t_fdf *f);
bool	parse_file(t_fdf *fdf, char *filename);
int		fdf_render(t_fdf *f);
void	fdf_init_edges(t_fdf *f);
void	draw_lines(t_fdf *f);

/*
 * HANDLERS
 */
int		key_press_handler(int keycode, void *mlx);
int		button_press_handler(int button, int x, int y, t_fdf *fdf);
int		button_release_handler(int button, int x, int y, t_fdf *fdf);
int		motion_handler(int x, int y, t_fdf *fdf);

/*
 * RENDER
 */
void	render_string(char *str, uint32_t *buf, int x, int y);
void	update_timer(t_renderer *r);

/*
 * PARSE INPUT
 */
bool	parse_chunk(t_parser *p, t_fdf *fdf, size_t chunk_end);

/*
 * MATRIX
 */
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

/*
 * TRANSFORMATION STACK
 */
void	make_transformation_stack(t_transformation_stack *t);
void	transformation_stack_rotate_x(t_transformation_stack *t, float dx);
void	transformation_stack_rotate_y(t_transformation_stack *t, float dy);
void	transformation_stack_rotate_z(t_transformation_stack *t, float dz);
void	transformation_stack_rview_x(t_transformation_stack *t, float dx);
void	transformation_stack_rview_y(t_transformation_stack *t, float dy);
void	transformation_stack_rview_z(t_transformation_stack *t, float dz);
void	transformation_stack_update(t_transformation_stack *t);
void	transformation_stack_ortho(
			t_transformation_stack *t,
			float x,
			float y,
			float z
			);
void	transformation_stack_zoom(t_transformation_stack *t, int direction);
void	transformation_stack_translate(
			t_transformation_stack *t,
			float dx,
			float dy,
			float dz
			);
void	transformation_stack_pan(
			t_transformation_stack *t,
			float dx,
			float dy,
			float dz
			);
void	transformation_stack_origin(
			t_transformation_stack *t,
			float dx,
			float dy,
			float dz
			);
void	transformation_update_projection(t_transformation_stack *t);

/*
 * UTIL
 */
int		ft_strntoi(int *n, char *str, size_t max);
bool	strntohex(uint32_t *n, char *str, char *end);
bool	ft_realloc(void **ptr, size_t *cap, size_t start);

#endif
