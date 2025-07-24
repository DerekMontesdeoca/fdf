/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:40:11 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/31 19:06:55 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		len;

	len = 0;
	current = lst;
	while (current != NULL)
	{
		++len;
		current = current->next;
	}
	return (len);
}
