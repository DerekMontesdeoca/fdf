/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:58:07 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 21:58:08 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "fdf.h"
#include "libft/libft.h"

static inline bool	is_delim(char c)
{
	return (c == ' ' || c == '\n');
}

static bool	advance_line(t_parser *p, t_fdf *fdf)
{
	p->x = 0;
	++p->y;
	++fdf->height;
	if (!p->width_set)
	{
		p->width_set = true;
		fdf->width = (int)p->values_read;
	}
	else
	{
		if ((size_t)p->y * fdf->width != p->values_read)
		{
			ft_fprintf(STDERR_FILENO, "Error: Rows of different"
				" sizes not allowed");
			return (false);
		}
	}
	return (true);
}

static inline void	push_value(t_parser *p, t_point4 *points)
{
	points[p->values_read].x = (float)p->x;
	points[p->values_read].y = (float)p->y;
	points[p->values_read].z = (float)p->z;
	if (!p->z_set || p->z < p->min_z)
		p->min_z = p->z;
	if (!p->z_set || p->z > p->max_z)
		p->max_z = p->z;
	p->z_set = true;
	++p->values_read;
	++p->x;
}

static inline int	skip_to_delim(char *buf, int end, int i)
{
	while (i < end && is_delim(buf[i]))
		++i;
	return (i);
}

bool	parse_chunk(t_parser *p, t_fdf *fdf, size_t chunk_end)
{
	size_t	i;
	int		number_len;

	i = 0;
	while (true)
	{
		i = skip_to_delim(p->buf, chunk_end, i);
		if (i == chunk_end)
			break ;
		number_len = ft_strntoi(&p->z, &p->buf[i], chunk_end - i);
		if (number_len == 0 || (i + number_len < chunk_end
				&& !is_delim(p->buf[i + number_len])))
			return (false);
		i += number_len;
		if (sizeof(t_point4[p->values_read]) >= p->arr_capacity && !ft_realloc(
				(void**)&fdf->points, &p->arr_capacity, sizeof(t_point4[4096])))
			return (false);
		push_value(p, fdf->points);
		while (i < chunk_end && p->buf[i] == ' ')
			++i;
		if (((i == chunk_end && p->bytes_read == 0) || p->buf[i] == '\n')
			&& !advance_line(p, fdf))
			return (false);
	}
	return (true);
}
