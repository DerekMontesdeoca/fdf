/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:32:03 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/23 12:52:04 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
			out[y] += m[y * 4 + x] * v[x];
			++x;
		}
		++y;
	}
}
