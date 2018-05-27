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
	int		j;

	room->weight = weight;
	if (room->special_room == 's')
		return ;
	j = 0;
	while (j < anthill->rooms_nb)
	{
		if (anthill->adj_matrix[room->id][j] == 1
			&& (anthill->rooms_array[j]->weight == 0
				|| anthill->rooms_array[j]->weight > weight))
		{
			ft_putstr("poids : ");
			ft_putnbr_endl(anthill->rooms_array[j]->weight);
			assign_weight_on(anthill->rooms_array[j], weight + 1, anthill);
		}
		j++;
	}
}

int			assign_weights(t_graph *anthill, t_parsing *data)
{
	t_room	*start;

	if (!anthill->rooms_array || !data->start || !data->end)
		return (-1);
	assign_weight_on(get_special_room(anthill, 'e'), 1, anthill);
	start = get_special_room(anthill, 's');
	if (!start->weight)
		return (-1);
	return (0);
}
