/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_start_room_movement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:35:01 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/19 09:35:03 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_favorable_start_to(t_room *dest, t_room *best_way,
													t_graph *anthill)
{
	return (dest->weight - best_way->weight <= anthill->ants_in_start);
}

static int		start_is_empty(t_graph *anthill)
{
	return (anthill->next_ant > anthill->ants_nb);
}

static t_room	*best_other_way(t_room *current)
{
	t_list	*link;
	t_room	*best;
	t_room	*tmp_room;

	best = NULL;
	link = current->links;
	int i =0;
	while (link)
	{
		tmp_room = (t_room *)link->content;
		if (tmp_room->special_room != START
			&& tmp_room->weight != 0
			&& tmp_room->ant == 0)
		{
			if (!best
				|| (best && tmp_room->weight < best->weight))
			{
				best = tmp_room;
			}
		}
		i++;
		link = link->next;
	}
	return (best);
}

void			move_in_start_room(t_graph *anthill)
{
	t_room	*start;
	t_room	*best_way;
	t_room	*other_way;

	if (start_is_empty(anthill))
		return ;
	start = get_special_room(anthill, START);
	best_way = best_room_to_choose(start);
	move_ant(start, best_way, anthill->next_ant, anthill);
	while (best_way && !(start_is_empty(anthill))
			&& (other_way = best_other_way(start))
			&& is_favorable_start_to(other_way, best_way, anthill))
	{
		move_ant(start, other_way, anthill->next_ant, anthill);
	}
}
