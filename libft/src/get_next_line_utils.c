/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 05:21:25 by dmontesd          #+#    #+#             */
/*   Updated: 2025/04/22 05:33:26 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	unsigned char	*old_ptr;
	unsigned char	*new_ptr;

	old_ptr = ptr;
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	while (old_size--)
		new_ptr[old_size] = old_ptr[old_size];
	free(ptr);
	return (new_ptr);
}

void	dynstr_init(t_dynstr *str)
{
	str->len = 0;
	str->size = 0;
	str->data = NULL;
}

bool	dynstr_ensure_size(t_dynstr *str, size_t ensured)
{
	size_t	new_size;
	char	*new_data;

	if (ensured <= str->size)
		return (true);
	new_size = str->size;
	while (new_size < ensured)
	{
		if (new_size == 0)
			new_size = 128;
		else
			new_size *= 2;
	}
	new_data = ft_realloc(str->data, str->size, new_size);
	if (new_data == NULL)
		return (false);
	str->data = new_data;
	str->size = new_size;
	return (true);
}

t_buf	*get_buf(void)
{
	static t_buf	buf;

	return (&buf);
}
