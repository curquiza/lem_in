/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_anthill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:57:00 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 18:58:08 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_del_rooms_array(t_room ***tab)
{
	free(*tab);
	*tab = NULL;
}

static void	del_links(t_list **links)
{
	t_list	*tmp;
	t_list	*supp;

	if (!links || !*links)
		return ;
	tmp = *links;
	while (tmp)
	{
		supp = tmp;
		tmp = tmp->next;
		free(supp);
	}
}

static void	ft_del_rooms_list(t_room **alst)
{
	t_room	*current;
	t_room	*tmp;

	if (!alst)
		return ;
	current = *alst;
	while (current)
	{
		tmp = current;
		ft_strdel(&current->name);
		del_links(&current->links);
		current = current->next;
		free(tmp);
	}
	*alst = NULL;
}

void		del_anthill(t_graph *anthill)
{
	ft_del_rooms_list(&anthill->rooms_list);
	ft_del_rooms_array(&anthill->rooms_array);
	ft_bzero(anthill, sizeof(*anthill));
}
