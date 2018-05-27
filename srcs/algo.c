#include "lem-in.h"

static t_room	*switch_rooms(t_room *room_1, t_room *rooms_2)
{
	room_1->next = rooms_2->next;
	rooms_2->next = room_1;
	return (rooms_2);
}

static t_room	*sort_rooms(t_room *room)
{
	if (!room)
		return (NULL);
	if (room->next && room->weight > room->next->weight)
		room = switch_rooms(room, room->next);
	room->next = sort_rooms(room->next);
	if (room->next && room->weight > room->next->weight)
	{
		room = switch_rooms(room, room->next);
		room->next = sort_rooms(room->next);
	}
	return (room);
}

void	algo(t_graph *anthill)
{
	anthill->rooms_list = sort_rooms(anthill->rooms_list);
}
