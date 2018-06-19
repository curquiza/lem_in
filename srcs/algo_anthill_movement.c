/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_anthill_movement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 09:33:43 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/19 09:34:17 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Conditions :
** - no ant in the next room
** - next room weight is lower than the current one
*/

t_room	*best_room_to_choose(t_room *current)
{
	t_list	*link;
	t_room	*best;
	t_room	*tmp_room;

	best = NULL;
	link = current->links;
	while (link)
	{
		tmp_room = (t_room *)link->content;
		if (tmp_room->special_room != START
			&& tmp_room->weight != 0
			&& tmp_room->ant == 0
			&& tmp_room->weight <= current->weight)
		{
			if (!best
				|| (best && tmp_room->weight < best->weight))
			{
				best = tmp_room;
			}
		}
		link = link->next;
	}
	return (best);
}

void	move_ant(t_room *from, t_room *dest, int ant, t_graph *anthill)
{
	if (dest)
	{
		ft_putchar('L');
		ft_putnbr(ant);
		ft_putchar('-');
		ft_putstr(dest->name);
		ft_putchar(' ');
		if (dest->special_room == END)
			anthill->ants_in_end += 1;
		else
			dest->ant = ant;
		from->ant = 0;
		if (from->special_room == START)
		{
			anthill->next_ant += 1;
			anthill->ants_in_start -= 1;
		}
	}
}

void	move_in_anthill(t_graph *anthill)
{
	t_room	*room;
	t_room	*best_way;

	room = anthill->rooms_list;
	while (room)
	{
		if (room->ant && room->special_room != START)
		{
			best_way = best_room_to_choose(room);
			move_ant(room, best_way, room->ant, anthill);
		}
		room = room->next;
	}
	move_in_start_room(anthill);
}
