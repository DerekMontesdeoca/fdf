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

static inline bool is_delim(char c)
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
        if ((size_t)p->y * fdf->width + p->x != p->values_read)
        {
            ft_fprintf(STDERR_FILENO, "Error: Rows of different"
                    " sizes not allowed");
            return (false);
        }
    }
    return (true);
}

static inline void    push_value(t_parser *p, t_fdf *fdf )
{
    fdf->points[p->values_read].x = (float)p->x;
    fdf->points[p->values_read].y = (float)p->y;
    fdf->points[p->values_read].z = (float)p->z;
    ++p->values_read;
    ++p->x;
}

bool parse_buffer(t_parser *p, t_fdf *fdf, char *buf, size_t end)
{
    size_t i;
    int number_len;

    i = 0;
    while (true)
    {
        while (i < end && is_delim(buf[i]))
            ++i;
        if (i == end)
            break;
        number_len = ft_strntoi(&p->z, &buf[i], end - i);
        if (number_len <= 0)
            return (false);
        i += number_len;
        if (sizeof(t_point3[p->values_read]) >= p->arr_capacity)
            if (!ft_realloc((void**)&fdf->points, &p->arr_capacity, sizeof(t_point3[4096])))
                return (false);
        push_value(p, fdf);
        while (i < end && buf[i] == ' ')
            ++i;
        if ((i == end && p->bytes_read == 0) || buf[i] == '\n')
            if (!advance_line(p, fdf))
                return (false);
    }
    return (true);
}
