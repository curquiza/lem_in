/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assign_weight.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:07:21 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 19:07:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*get_special_room(t_graph *anthill, int special_room)
{
	t_room	*tmp;

	tmp = anthill->rooms_list;
	while (tmp && tmp->special_room != special_room)
		tmp = tmp->next;
	return (tmp);
}

static void	assign_weight_on(t_room *room, int weight, t_graph *anthill)
{
	t_list	*link;

	if (room->weight == 0 || room->weight > weight)
	{
		room->weight = weight;
		link = room->links;
		if (room->special_room == START)
			return ;
		while (link)
		{
			assign_weight_on(link->content, weight + 1, anthill);
			link = link->next;
		}
	}
}

int			assign_weights(t_graph *anthill, t_parsing *data)
{
	t_room	*start;

	if (!anthill->rooms_list || !data->start || !data->end)
		return (-1);
	assign_weight_on(get_special_room(anthill, END), 1, anthill);
	start = get_special_room(anthill, START);
	if (!start->weight)
		return (-1);
	return (0);
}
