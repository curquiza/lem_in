#include "lem-in.h"

static t_room	*switch_rooms(t_room *room_1, t_room *rooms_2)
{
	room_1->next = rooms_2->next;
	rooms_2->next = room_1;
	return (rooms_2);
}

static t_room	*sort_rooms(t_room *rooms)
{
	if (!rooms)
		return (NULL);
	if (rooms->next && rooms->next->weight < rooms->weight)
		rooms = switch_rooms(rooms, rooms->next);
	rooms->next = sort_rooms(rooms->next);
	if (rooms->next && rooms->next->weight < rooms->weight)
	{
		rooms = switch_rooms(rooms, rooms->next);
		rooms->next = sort_rooms(rooms->next);
	}
	return (rooms);
}

/*
** Conditions :
** - no ant in the next room
** - next room weight is lower than the current one
*/
t_room	*best_room_to_choose(t_room *current, t_graph *anthill)
{
	int		j;
	t_room	*best;

	best = NULL;
	j = 0;
	while (j < anthill->rooms_nb)
	{
		if (anthill->adj_matrix[current->id][j]
			&& anthill->rooms_array[j]->special_room != 's'
			&& anthill->rooms_array[j]->weight != 0
			&& anthill->rooms_array[j]->ant == 0
			&& anthill->rooms_array[j]->weight <= current->weight)
		{
			if (!best
				|| (best && anthill->rooms_array[j]->weight < best->weight))
			{
				best = anthill->rooms_array[j];
			}
		}
		j++;
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
		if (dest->special_room == 'e')
			anthill->ants_in_end += 1;
		else
			dest->ant = ant;
		from->ant = 0;
		if (from->special_room == 's')
		{
			anthill->next_ant += 1;
			anthill->ants_in_start -= 1;
		}
	}
}

int		is_favorable_start_to(t_room *dest, t_room *best_way, t_graph *anthill)
{
	if (dest->weight - best_way->weight <= anthill->ants_in_start)
		return (1);
	return (0);
}

int		start_is_empty(t_graph *anthill)
{
	return (anthill->next_ant > anthill->ants_nb);
}

void	move_in_start_room(t_graph *anthill)
{
	t_room	*start;
	t_room	*best_way;
	t_room	*other_way;

	if (start_is_empty(anthill))
		return ;
	start = get_special_room(anthill, 's');
	best_way = best_room_to_choose(start, anthill);
	move_ant(start, best_way, anthill->next_ant, anthill);
	while (best_way && !(start_is_empty(anthill))
			&& (other_way = best_room_to_choose(start, anthill))
			&& is_favorable_start_to(other_way, best_way, anthill))
	{
		move_ant(start, other_way, anthill->next_ant, anthill);
	}
}

void	move_in_anthill(t_graph *anthill)
{
	t_room	*room;
	t_room	*best_way;

	room = anthill->rooms_list;
	while (room)
	{
		if (room->ant && room->special_room != 's')
		{
			// ft_putendl2_fd("room name = ", room->name, 1);
			best_way = best_room_to_choose(room, anthill);
			move_ant(room, best_way, room->ant, anthill);
		}
		room = room->next;
	}
	move_in_start_room(anthill);
}

void	algo(t_graph *anthill)
{
	anthill->rooms_list = sort_rooms(anthill->rooms_list);
	anthill->ants_in_start = anthill->ants_nb;
	anthill->next_ant = 1;
	ft_putchar('\n');
	while (anthill->ants_in_end < anthill->ants_nb)
	{
		// ft_putnbr2("ants in end : ", anthill->ants_in_end);
		// ft_putnbr2("ants in start : ", anthill->ants_in_start);
		// ft_putnbr2("next ants : ", anthill->next_ant);
		move_in_anthill(anthill);
		ft_putchar('\n');
		// if (anthill->ants_in_end == 6)
		// 	break;
	}
}
