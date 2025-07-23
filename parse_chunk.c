/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:58:07 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/24 00:18:14 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "fdf.h"
#include "libft/libft.h"

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
	else if (p->values_read > (size_t)p->y * fdf->width)
	{
		ft_fprintf(STDERR_FILENO, "Error: Bad map\n");
		return (false);
	}
	else if (p->values_read < (size_t)p->y * fdf->width)
	{
		if (!realloc_all(p, fdf))
			return (false);
		while (p->values_read < (size_t)p->y * fdf->width)
		{
			fdf->points[p->values_read] = 0;
			fdf->color[p->values_read] = 0xffffff;
			++p->values_read;
		}
	}
	return (true);
}

static inline void	push_value(t_parser *p, t_fdf *fdf)
{
	fdf->color[p->values_read] = p->color;
	fdf->points[p->values_read] = (float)p->z;
	if (!p->z_set || p->z < p->min_z)
		p->min_z = p->z;
	if (!p->z_set || p->z > p->max_z)
		p->max_z = p->z;
	p->z_set = true;
	++p->values_read;
	++p->x;
}

static inline bool	parse_value(
	t_parser *p,
	size_t chunk_size,
	size_t *i
) {
	int		number_len;

	number_len = ft_strntoi(&p->z, &p->buf[*i], chunk_size - *i);
	if (number_len == 0)
		return (false);
	*i += number_len;
	if (!parse_color(p, chunk_size, i))
		return (false);
	if (*i + number_len < chunk_size && !is_delim(p->buf[*i]))
		return (false);
	return (true);
}

bool	parse_chunk(t_parser *p, t_fdf *fdf, size_t chunk_size)
{
	size_t	i;

	i = 0;
	while (true)
	{
		i = skip_delim(p->buf, chunk_size, i);
		if (i == chunk_size)
			break ;
		if (!parse_value(p, chunk_size, &i))
			return (false);
		if (!realloc_all(p, fdf))
			return (false);
		push_value(p, fdf);
		while (i < chunk_size && p->buf[i] == ' ')
			++i;
		if (((i == chunk_size && p->bytes_read == 0) || p->buf[i] == '\n')
			&& !advance_line(p, fdf))
			return (false);
	}
	return (true);
}
