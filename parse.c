/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:25:53 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 18:26:00 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "fdf.h"
#include "libft/libft.h"

#define INPUT_BUF_SIZE 4096

static inline bool	is_delim(char c)
{
	return (c == ' ' || c == '\n');
}

static bool	find_last_delimiter(t_parser *p, char *buf, size_t read_start)
{
	bool	delim_found;

	if (p->bytes_read == 0)
		p->last_delim = read_start;
	else
	{
		p->last_delim = read_start + p->bytes_read;
		delim_found = false;
		while (p->last_delim-- > 0)
		{
			if (is_delim(buf[p->last_delim]))
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
	return (true);
}

static bool	parse_file_inner(t_parser *p, t_fdf *fdf, int fd, char *buf)
{
	size_t			read_start;

	read_start = 0;
	while (true)
	{
		p->bytes_read = read(fd, buf + read_start, INPUT_BUF_SIZE - read_start);
		if (p->bytes_read < 0)
			return (false);
		if (p->bytes_read == 0 && read_start == 0)
			break ;
		if (!find_last_delimiter(p, buf, read_start))
			return (false);
		parse_buffer(p, fdf, buf, p->last_delim);
		if (p->bytes_read == 0)
			break ;
		// Move remaining string after last delimiter to the beginning
		// of the buffer.
		ft_memmove(buf, &buf[p->last_delim + 1],
			read_start + p->bytes_read - p->last_delim - 1);
		read_start = read_start + p->bytes_read - p->last_delim - 1;
	}
	return (true);
}

bool	parse_file(t_fdf *fdf)
{
	char		*buf;
	bool		ok;
	t_parser	parser;

	buf = malloc(INPUT_BUF_SIZE);
	parser = (t_parser){0};
	if (buf == NULL)
		return (false);
	ok = parse_file_inner(&parser, fdf, STDIN_FILENO, buf);
	free(buf);
	return (ok);
}
