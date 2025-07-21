
#include "libft/libft.h"

void	matrix4_dot_product(const float *m, float *v, float *out)
{
	int	x;
	int	y;

	y = 0;
	ft_memset(out, 0, sizeof(float[4]));
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			out[x] += m[y * 4 + x] * v[x];
			++x;
		}
		++y;
	}
}
