#include "lem-in.h"

int			is_valid_tube(char *line)
{
	char	**tube_data;

	tube_data = ft_strsplit(line, ' ');
	if (!tube_data || ft_tablen(tube_data) != 1)
	{
		ft_tabdel(&tube_data);
		return (0);
	}
	ft_tabdel(&tube_data);
	tube_data = ft_strsplit(line, '-');
	if (!tube_data || ft_tablen(tube_data) != 2)
	{
		ft_tabdel(&tube_data);
		return (0);
	}
	ft_tabdel(&tube_data);
	return (1);
}

void		create_adj_matrix(t_graph *anthill)
{
	int		i;

	anthill->adj_matrix = ft_memalloc(sizeof(*anthill->adj_matrix) * anthill->rooms_nb);
	i = 0;
	while (i < anthill->rooms_nb)
	{
		anthill->adj_matrix[i] = ft_memalloc(sizeof(**anthill->adj_matrix) * anthill->rooms_nb);
		i++;
	}
}

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
