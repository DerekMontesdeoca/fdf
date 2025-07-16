/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:54:47 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 15:54:49 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/libft.h"

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