#include "lem-in.h"

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
		add_tube_to_anthill(line, anthill, data);
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

// void	ft_put_adj_matrix(int **tab, t_parsing *data)
// {
// 	int		i;
// 	int		j;
//
// 	i = 0;
// 	while (i < data->rooms_nb)
// 	{
// 		j = 0;
// 		while (j < data->rooms_nb)
// 		{
// 			ft_putnbr(tab[i][j]);
// 			ft_putchar(' ');
// 			j++;
// 		}
// 		ft_putendl("");
// 		i++;
// 	}
// }
//
// void	ft_put_all_rooms(t_room **rooms, t_parsing *data)
// {
// 	int		i;
//
// 	i = 0;
// 	while (i < data->rooms_nb)
// 	{
// 		ft_putstr("id : ");
// 		ft_putnbr_endl(rooms[i]->id);
// 		ft_putstr("name : ");
// 		ft_putendl(rooms[i]->name);
// 		ft_putendl("");
// 		i++;
// 	}
// }

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
	read_end_of_inputs(&data);
	if (data.input && assign_weight(anthill, &data) != -1)
		write(1, data.input, ft_strlen(data.input));
	else
	{
		ft_strdel(&data.input);
		return (-1);
	}
	ft_strdel(&data.input);
	return (0);
}
