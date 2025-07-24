/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontesd <dmontesd@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:40:11 by dmontesd          #+#    #+#             */
/*   Updated: 2025/01/31 19:06:38 by karlarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <stdlib.h>

static t_list	*lst_new_mapped_node(
	void *content, void *(*f)(void *), void (*del)(void *)
) {
	t_list	*new_node;
	void	*new_content;

	if (f == NULL)
		return (NULL);
	new_content = f(content);
	if (new_content == NULL)
		return (NULL);
	new_node = ft_lstnew(new_content);
	if (new_node == NULL)
	{
		if (del != NULL)
			del(new_content);
		return (NULL);
	}
	new_node->content = new_content;
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*prev_new_node;
	t_list	*new_node;

	if (lst == NULL)
		return (NULL);
	new_list = lst_new_mapped_node(lst->content, f, del);
	if (new_list == NULL)
		return (NULL);
	lst = lst->next;
	prev_new_node = new_list;
	while (lst != NULL)
	{
		new_node = lst_new_mapped_node(lst->content, f, del);
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		prev_new_node->next = new_node;
		prev_new_node = new_node;
		lst = lst->next;
	}
	return (new_list);
}
