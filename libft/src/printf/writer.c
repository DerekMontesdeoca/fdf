/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:59:34 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/07 04:27:57 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "writer.h"

/*
 * Does not zero initialize the buffer. Zero initializes the variables.
 */
void	writer_reset(t_writer *w)
{
	w->index = 0;
	w->error = 0;
	w->n_written = 0;
}

bool	writer_write(t_writer *w, const char *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && writer_putchar(w, mem[i]))
		++i;
	return (w->error >= 0);
}

int	writer_flush(t_writer *w)
{
	size_t	n_written;
	size_t	total_written;

	total_written = 0;
	while (total_written < w->index)
	{
		n_written = write(w->fd, w->buf + total_written,
				w->index - total_written);
		if (n_written < 0)
			return (w->error = n_written, n_written);
		total_written += n_written;
	}
	w->index = 0;
	w->n_written += total_written;
	return (total_written);
}

bool	writer_is_full(t_writer *w)
{
	return (w->index == BUF_SIZE);
}

bool	writer_putchar(t_writer *w, char c)
{
	if (writer_is_full(w) && writer_flush(w) < 0)
		return (false);
	w->buf[w->index] = c;
	w->index++;
	return (true);
}
