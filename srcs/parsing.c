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

int		get_ants_number(t_graph *anthill, t_parsing *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == 1 && line)
	{
		if (str_is_digit(line) && ft_strlen(line) < 8)
		{
			anthill->ants_nb = ft_atoi(line);
			record_input_line(&line, data);
			return (anthill->ants_nb ? 0 : -1);
		}
		else if (!is_comment(line))
		{
			record_input_line(&line, data);
			return (-1);
		}
		record_input_line(&line, data);
	}
	record_input_line(&line, data);
	return (-1);
}

int		is_valid_room(char *line)
{
	char	*room_data;
	
	room_data = ft_strsplit(line, ' ');
	if (!room_data || ft_tablen(room_data) != 3)
		return (0);
	if (room_data[0][0] == 'L'
		|| !str_is_digit(room_data[1]) || str_is_digit(room_data[2]))
		return (0);
	return (1);
}

int		is_valid_input(char *line, t_parsing *data)
{
	if (data->rooms_done == 0)
		return (is_valid_room(line));
	return (is_valid_tube(line));
}

void	add_room_to_anthill(char *line, t_graph *anthill)
{
	(void)line;
	(void)anthill;
}

void	add_tube_to_anthill(char *line, t_graph *anthill)
{
	(void)line;
	(void)anthill;
}

void	add_input_to_anthill(char *line, t_parsing *data, t_graph *anthill)
{
	if (data->rooms_done == 0)
		add_room_to_anthill(line, anthill);
	else
		add_tube_to_anthill(line, anthill);
}

int		get_rooms_and_tubes(t_graph *anthill, t_parsing *data)
{
	char	*line;

	(void)anthill;
	line = NULL;
	while (get_next_line(0, &line) == 1 && line)
	{
		if (is_valid_command(line))
		{
			; // do stuff for ##start or ##end
			; // si start ou end dans tube -> stop = 0
			; // si 2 start ou end -> error = -1
		}
		else if (!is_comment(line))
		{
			if (!is_valid_input(line))
			{
				record_input_line(&line, data);
				return (0);
			}
			else
				add_input_to_anthill(line, data, anthill);
		}
		record_input_line(&line, data);
	}
	record_input_line(&line, data);
	return (-1);
}

int		parser(t_graph *anthill)
{
	t_parsing	data;

	ft_bzero(&data, sizeof(t_parsing));
	if (get_ants_number(anthill, &data) != 0)
		return (-1);
	if (get_rooms_and_tubes(anthill, &data) != 0)
		return (-1);
	return (0);
}