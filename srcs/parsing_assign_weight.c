#include "lem-in.h"

t_room		*get_special_room(t_graph *anthill, int special_room)
{
	int		i;

	i = 0;
	while (anthill->rooms_array[i]->special_room != special_room)
		i++;
	return (anthill->rooms_array[i]);
}

static void	assign_weight_on(t_room *room, int weight, t_graph *anthill)
{
	t_list	*link;

	if (room->weight == 0 || room->weight > weight)
	{
		room->weight = weight;
		link = room->links;
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

	if (!anthill->rooms_array || !data->start || !data->end)
		return (-1);
	assign_weight_on(get_special_room(anthill, END), 1, anthill);
	start = get_special_room(anthill, START);
	if (!start->weight)
		return (-1);
	return (0);
}
