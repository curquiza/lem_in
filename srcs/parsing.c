#include "lem-in.h"

void	record_input_line(char **line, t_parsing *data)
{
	char	*buff;
	int		old_len;
	int		line_len;

	line_len = *line ? ft_strlen(*line) : 0;
	old_len = data->input ? ft_strlen(data->input) : 0;
	buff = data->input;
	data->input = ft_strnew(old_len + line_len + 1);
	if (buff)
		ft_strcpy(data->input, buff);
	if (*line)
		ft_strcpy(data->input + old_len, *line);
	data->input[old_len + line_len] = '\n';
	ft_strdel(line);
	ft_strdel(&buff);
}

int		is_valid_room(char *line)
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

int		is_valid_tube(char *line)
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

void	create_adj_matrix(t_graph *anthill, t_parsing *data)
{
	int		i;

	anthill->adj_matrix = ft_memalloc(sizeof(*anthill->adj_matrix) * data->rooms_nb);
	i = 0;
	while (i < data->rooms_nb)
	{
		anthill->adj_matrix[i] = ft_memalloc(sizeof(**anthill->adj_matrix) * data->rooms_nb);
		i++;
	}
}

void	create_rooms_array(t_graph *anthill, t_parsing *data)
{
	int		i;
	t_room	*tmp;

	anthill->rooms_array = ft_memalloc(sizeof(*anthill->rooms_array) * data->rooms_nb);
	tmp = anthill->rooms_list;
	i = 0;
	while (tmp)
	{
		anthill->rooms_array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
}

int		is_valid_input(char *line, t_graph *anthill, t_parsing *data)
{
	if (data->rooms_reading_done == 0)
	{
		if (is_valid_room(line))
			return (1);
		else if (is_valid_tube(line))
		{
			data->rooms_reading_done = 1;
			create_adj_matrix(anthill, data);
			create_rooms_array(anthill, data);
			return (1);
		}
		return (0);
	}
	else
		return (is_valid_tube(line));
}

void	add_input_to_anthill(char *line, t_parsing *data, t_graph *anthill)
{
	if (data->rooms_reading_done == 0)
		add_room_to_anthill(line, anthill, data, 0);
	else
		add_tube_to_anthill(line, anthill);
}

int		manage_valid_command(char **line, t_parsing *data, t_graph *anthill)
{
	int		command;

	command = is_end_command(*line) ? 'e' : 's';
	record_input_line(line, data);
	if (data->rooms_reading_done == 1
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
	add_room_to_anthill(*line, anthill, data, command);
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

int		assign_weight(t_graph *anthill)
{
	(void)anthill;
	//check si presence de end et de start
	//repartir les poids des salles => check au passage si un path existe
	return (0);
}

int		parser(t_graph *anthill)
{
	t_parsing	data;

	ft_bzero(&data, sizeof(t_parsing));
	if (get_ants_number(anthill, &data) != 0)
	{
		ft_strdel(&data.input);
		return (-1);
	}
	get_rooms_and_tubes(anthill, &data);
	//continuer de lire jusqu'à la fin
	if (data.input) // && assign_weight(anthill) != -1
		write(1, data.input, ft_strlen(data.input));
	ft_strdel(&data.input);
	return (0);
}
