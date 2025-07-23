
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
	vec[3] = 0;
	matrix4_dot_product(t->combined, vec, result);
	transformation_stack_pan(t, 0,
		result[1] * (t->projection.b - t->projection.t) / 2);
}
