#include "lem-in.h"

static void	add_input_to_anthill(char *line, t_parsing *data, t_graph *anthill)
{
	if (data->rooms_reading_done == 0)
		add_room_to_anthill(line, anthill, data, 0);
	else
		add_tube_to_anthill(line, anthill);
}

static int	manage_valid_command(char **line, t_parsing *data, t_graph *anthill)
{
	int		command;

	command = is_end_command(*line) ? END : START;
	record_input_line(line, data);
	if (data->rooms_reading_done == 1
		|| (command == END && data->end == 1)
		|| (command == START && data->start == 1))
		return (-1);
	if (get_next_line(0, line) != 1 || !line)
		return (-1);
	if (is_valid_tube(*line) || !is_valid_room(*line))
	{
		record_input_line(line, data);
		return (-1);
	}
	add_room_to_anthill(*line, anthill, data, command);
	return (0);
}

static void	get_rooms_and_tubes(t_graph *anthill, t_parsing *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == 1 && line)
	{
		if (is_valid_command(line))
		{
			if (manage_valid_command(&line, data, anthill) == -1)
				return ;
		}
		else if (!is_comment(line))
		{
			if (!is_valid_input(line, anthill, data))
			{
				record_input_line(&line, data);
				return ;
			}
			add_input_to_anthill(line, data, anthill);
		}
		record_input_line(&line, data);
	}
}

int			parser(t_graph *anthill)
{
	t_parsing	data;

	ft_bzero(&data, sizeof(t_parsing));
	if (get_ants_number(anthill, &data) != 0)
	{
		ft_strdel(&data.input);
		return (-1);
	}
	get_rooms_and_tubes(anthill, &data);
	if (!data.input || assign_weights(anthill, &data) == -1)
	{
		ft_strdel(&data.input);
		return (-1);
	}
	read_end_of_inputs(&data);
	write(1, data.input, ft_strlen(data.input));
	ft_strdel(&data.input);
	return (0);
}
