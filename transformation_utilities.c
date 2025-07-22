
#include "fdf.h"
#include "libft/libft.h"

// static inline void	center_model(t_transformation_stack *t, float height)
// {
// 	t->projection.box[0] / 2;
// 	t->projection.box[1] / 2;
// 	t->projection.box[2] / 2;
// 	transformation_stack_pan()
// }

// static inline void	center_model(t_transformation_stack *t, float height)
// {
// 	float	vec[4];
// 	float	result[4];
// 	float	top;
//
// 	ft_memset(vec, 0 , sizeof(vec));
// 	vec[1] = 0;
// 	vec[2] = t->tz;
// 	matrix4_dot_product(t->combined, vec, result);
// 	top = result[1];
// 	ft_memset(vec, 0 , sizeof(vec));
// 	vec[1] = -height;
// 	vec[2] = t->tz;
// 	matrix4_dot_product(t->combined, vec, result);
// 	transformation_stack_pan(t, 0, top-vec[1]/2);
// }
