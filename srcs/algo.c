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

void	algo(t_graph *anthill)
{
	anthill->rooms_list = sort_rooms(anthill->rooms_list);
}
