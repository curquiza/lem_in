#include "lem_in.h"

static int		is_favorable_start_to(t_room *dest, t_room *best_way,
													t_graph *anthill)
{
	if (dest->weight - best_way->weight <= anthill->ants_in_start)
		return (1);
	return (0);
}

static int		start_is_empty(t_graph *anthill)
{
	return (anthill->next_ant > anthill->ants_nb);
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
			&& (other_way = best_room_to_choose(start))
			&& is_favorable_start_to(other_way, best_way, anthill))
	{
		move_ant(start, other_way, anthill->next_ant, anthill);
	}
}
