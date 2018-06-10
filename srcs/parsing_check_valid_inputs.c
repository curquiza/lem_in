#include "lem-in.h"

int			is_valid_tube(char *line)
{
	char	*tmp;

	if (!line
		|| *line == '-'
		|| ft_strchr(line, ' ')
		|| !(tmp = ft_strchr(line, '-'))
		|| tmp != ft_strrchr(line, '-')
		|| !*(tmp + 1))
		return (0);
	return (1);
}

int			is_valid_room(char *line)
{
	char	*tmp;

	if (!line || line[0] == 'L' || ft_strchr(line, '-'))
		return (0);
	if (!(tmp = ft_strchr(line, ' ')))
		return (0);
	line = tmp + 1;
	while (*line && *line != ' ')
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	if (!*line)
		return (0);
	line++;
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
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
