#include "lem-in.h"

/*
** Returns room id if found. Otherwise, returns -1
*/
static int	get_room_id(char *name, t_graph *anthill)
{
	int		i;

	i = 0;
	while (i < anthill->rooms_nb)
	{
		if (!ft_strcmp(anthill->rooms_array[i]->name, name))
			return (anthill->rooms_array[i]->id);
		i++;
	}
	return (-1);
}

void		add_tube_to_anthill(char *line, t_graph *anthill)
{
	char	**tubes;
	int		room_1;
	int		room_2;

	tubes = ft_strsplit(line, '-');
	if ((room_1 = get_room_id(tubes[0], anthill)) != -1
		&& (room_2 = get_room_id(tubes[1], anthill)) != -1)
	{
		anthill->adj_matrix[room_1][room_2] = 1;
		anthill->adj_matrix[room_2][room_1] = 1;
	}
	ft_tabdel(&tubes);
}
