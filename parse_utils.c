/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 00:08:46 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/24 00:21:05 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	realloc_all(t_parser *p, t_fdf *fdf)
{
	size_t	capacity;

	if (p->values_read >= p->arr_capacity)
	{
		capacity = sizeof(float [p->arr_capacity]);
		if (!ft_realloc((void **) &fdf->points, &capacity,
				sizeof(float [4096])))
			return (false);
		capacity = sizeof(uint32_t[p->arr_capacity]);
		if (!ft_realloc((void **) &fdf->color, &capacity,
				sizeof(uint32_t [4096])))
			return (false);
		p->arr_capacity = capacity / sizeof(*fdf->color);
	}
	return (true);
}

bool	parse_color(t_parser *p, size_t chunk_size, size_t *i)
{
	int	hex_len;

	if (*i < chunk_size && p->buf[*i] == ',')
	{
		if (*i == chunk_size || p->buf[*i] != ',')
			return (false);
		++*i;
		hex_len = strntohex(&p->color, &p->buf[*i], p->buf + chunk_size);
		if (hex_len == 0)
			return (false);
		*i += hex_len;
	}
	else
		p->color = 0xffffff;
	return (true);
}

bool	is_delim(char c)
{
	return (c == ' ' || c == '\n');
}

int	skip_delim(char *buf, int end, int i)
{
	while (i < end && is_delim(buf[i]))
		++i;
	return (i);
}
