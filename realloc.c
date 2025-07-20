/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:47:48 by dmontesd          #+#    #+#             */
/*   Updated: 2025/07/15 21:47:49 by dmontesd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft/libft.h"

bool	ft_realloc(void **ptr, size_t *cap, size_t start)
{
	size_t	new_cap;
	void	*temp;

	if (*cap == 0)
		new_cap = start;
	else
		new_cap = *cap * 2;
	temp = malloc(new_cap);
	if (temp == NULL)
		return (false);
	ft_memcpy(temp, *ptr, *cap);
	free(*ptr);
	*ptr = temp;
	*cap = new_cap;
	return (true);
}
