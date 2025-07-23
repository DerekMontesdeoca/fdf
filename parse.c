/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:25:53 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/24 00:16:51 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include "fdf.h"
#include "libft/libft.h"

#define INPUT_BUF_SIZE 4096

static inline bool	find_chunk_end(
	t_parser *p,
	char *buf,
	size_t leftover,
	size_t *chunk_end
) {
	bool	delim_found;
	size_t	end;

	if (p->bytes_read == 0)
		end = leftover;
	else
	{
		end = leftover + p->bytes_read;
		delim_found = false;
		while (end-- > 0)
		{
			if (is_delim(buf[end]))
			{
				delim_found = true;
				break ;
			}
		}
		if (!delim_found)
		{
			ft_fprintf(STDERR_FILENO, "Error: file input value too long");
			return (false);
		}
	}
	*chunk_end = end;
	return (true);
}

/**
 * Chunks represent the parseable end of the buffer. Whatever is after chunk end
 * is copied to the front of the buffer.
 */
static inline bool	parse_buffered(t_parser *p, t_fdf *fdf, int fd)
{
	size_t			leftover;
	size_t			chunk_end;

	leftover = 0;
	while (true)
	{
		p->bytes_read = read(fd, p->buf + leftover, INPUT_BUF_SIZE - leftover);
		if (p->bytes_read < 0)
			return (perror("read: "), false);
		if (p->bytes_read == 0 && leftover == 0)
			break ;
		if (!find_chunk_end(p, p->buf, leftover, &chunk_end))
			return (false);
		if (!parse_chunk(p, fdf, chunk_end))
			return (false);
		if (p->bytes_read == 0)
			break ;
		ft_memmove(p->buf, &p->buf[chunk_end + 1],
			leftover + p->bytes_read - chunk_end - 1);
		leftover = leftover + p->bytes_read - chunk_end - 1;
	}
	fdf->min_z = p->min_z;
	fdf->max_z = p->max_z;
	return (true);
}

bool	parse_file(t_fdf *fdf, char *filename)
{
	bool		ok;
	t_parser	parser;
	int			fd;

	ok = false;
	parser = (t_parser){0};
	parser.buf = malloc(INPUT_BUF_SIZE);
	fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		if (parser.buf != NULL)
			ok = parse_buffered(&parser, fdf, fd);
		close(fd);
	}
	else
		perror("open: ");
	free(parser.buf);
	return (ok);
}
