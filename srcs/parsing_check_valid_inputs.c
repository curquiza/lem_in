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

int			is_valid_room(char *line)
{
	char	**room_data;

	room_data = ft_strsplit(line, ' ');
	if (!room_data || ft_tablen(room_data) != 3)
	{
		ft_tabdel(&room_data);
		return (0);
	}
	if (room_data[0][0] == 'L' || ft_strchr(room_data[0], '-')
		|| !str_is_digit(room_data[1]) || !str_is_digit(room_data[2]))
	{
		ft_tabdel(&room_data);
		return (0);
	}
	ft_tabdel(&room_data);
	return (1);
}

static void	create_rooms_array(t_graph *anthill)
{
	int		i;
	t_room	*tmp;

	anthill->rooms_array = ft_memalloc(sizeof(*anthill->rooms_array)
										* anthill->rooms_nb);
	tmp = anthill->rooms_list;
	i = 0;
	while (tmp)
	{
		anthill->rooms_array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
}

void static	create_adj_matrix(t_graph *anthill)
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

int			is_valid_input(char *line, t_graph *anthill, t_parsing *data)
{
	if (data->rooms_reading_done == 0)
	{
		if (is_valid_room(line))
			return (1);
		else if (is_valid_tube(line))
		{
			data->rooms_reading_done = 1;
			create_adj_matrix(anthill);
			create_rooms_array(anthill);
			return (1);
		}
		return (0);
	}
	else
		return (is_valid_tube(line));
}
