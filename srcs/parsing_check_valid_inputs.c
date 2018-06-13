#include "lem-in.h"

bool		is_valid_tube(char *line)
{
	char	*tmp;

	if (!line
		|| *line == '-'
		|| ft_strchr(line, ' ')
		|| !(tmp = ft_strchr(line, '-'))
		|| tmp != ft_strrchr(line, '-')
		|| !*(tmp + 1))
		return (false);
	return (true);
}

bool		is_valid_room(char *line)
{
	char	*tmp;

	if (!line || line[0] == 'L' || ft_strchr(line, '-'))
		return (false);
	if (!(tmp = ft_strchr(line, ' ')))
		return (false);
	line = tmp + 1;
	while (*line && *line != ' ')
	{
		if (!ft_isdigit(*line))
			return (false);
		line++;
	}
	if (!*line)
		return (false);
	line++;
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (false);
		line++;
	}
	return (true);
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

bool		is_valid_input(char *line, t_graph *anthill, t_parsing *data)
{
	if (data->rooms_reading_done == 0)
	{
		if (is_valid_room(line))
			return (true);
		else if (is_valid_tube(line))
		{
			data->rooms_reading_done = 1;
			create_rooms_array(anthill);
			return (true);
		}
		return (false);
	}
	else
		return (is_valid_tube(line));
}
