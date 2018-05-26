#include "lem-in.h"

void	record_input_line(char **line, t_parsing *data)
{
	char	*buff;
	int		old_len;
	int		line_len;

	buff = data->input;
	line_len = *line ? ft_strlen(*line) : 0;
	old_len = data->input ? ft_strlen(data->input) : 0;
	data->input = ft_strnew(old_len + line_len);
	if (buff)
		ft_strcpy(data->input, buff);
	if (*line)
		ft_strcpy(data->input + old_len, *line);
	ft_strdel(line);
	ft_strdel(&buff);
}

int		is_valid_room(char *line)
{
	char	**room_data;

	room_data = ft_strsplit(line, ' ');
	if (!room_data || ft_tablen(room_data) != 3)
		return (0);
	if (room_data[0][0] == 'L' || ft_strchr(room_data[0], '-')
		|| !str_is_digit(room_data[1]) || str_is_digit(room_data[2]))
		return (0);
	return (1);
}

int		is_valid_tube(char *line)
{
	char	**tube_data;

	tube_data = ft_strsplit(line, ' ');
	if (!tube_data || ft_tablen(tube_data) != 1)
		return (0);
	ft_tabdel(&tube_data);
	tube_data = ft_strsplit(line, '-');
	if (!tube_data || ft_tablen(tube_data) != 2)
		return (0);
	return (1);
}

int		is_valid_input(char *line, t_parsing *data)
{
	if (data->rooms_done == 0)
	{
		if (is_valid_room(line))
			return (1);
		else if (is_valid_tube(line))
		{
			data->rooms_done = 1;
			//creer matrice adjacence
			//creer tableau des rooms
			return (1);
		}
		return (0);
	}
	else
		return (is_valid_tube(line));

}

void	add_input_to_anthill(char *line, t_parsing *data, t_graph *anthill)
{
	if (data->rooms_done == 0)
		add_room_to_anthill(line, anthill, 0);
	else
		add_tube_to_anthill(line, anthill);
}

int		manage_valid_command(char **line, t_parsing *data, t_graph *anthill)
{
	int		command;

	command = is_end_command(*line) ? 'e' : 's';
	record_input_line(line, data);
	if (data->rooms_done == 1
		|| (command == 'e' && data->end == 1)
		|| (command == 's' && data->start == 1))
		return (-1);
	if (get_next_line(0, line) != 1 || !line)
		return (-1);
	if (is_valid_tube(*line) || !is_valid_room(*line))
	{
		record_input_line(line, data);
		return (-1);
	}
	add_room_to_anthill(*line, anthill, command);
	return (0);
}

void	get_rooms_and_tubes(t_graph *anthill, t_parsing *data)
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
			if (!is_valid_input(line, data))
			{
				record_input_line(&line, data);
				return ;
			}
			add_input_to_anthill(line, data, anthill);
		}
		record_input_line(&line, data);
	}
}

int		parser(t_graph *anthill)
{
	t_parsing	data;

	ft_bzero(&data, sizeof(t_parsing));
	if (get_ants_number(anthill, &data) != 0)
		//continuer de lire jusqu'à la fin
		return (-1);
	get_rooms_and_tubes(anthill, &data);
	//continuer de lire jusqu'à la fin
	//check si presence de end et de start
	//repartir les poids des salles => check au passage si un path existe
	return (0);
}
