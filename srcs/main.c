#include "lem-in.h"

int		is_start_command(char *line)
{
	return (ft_strequ(line, "##start"));
}

int		is_end_command(char *line)
{
	return (ft_strequ(line, "##end"));
}

int		is_valid_command(char *line)
{
	return (is_start_command(line) || is_end_command(line));
}

int		is_comment(char *line)
{
	return (line[0] == '#');
}

int		str_is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	record_input_line(char **line, t_parsing *data)
{
	(void)data; //ajoute un maillon à la liste chainée avec la donnée de la ligne
	ft_strdel(line);
}

int		get_ants_number(t_graph *anthill, t_parsing *data)
{
	char	*line;

	line = NULL;
	while (42)
	{
		if (get_next_line(0, &line) != 1 || !line
			|| is_valid_command(line) || ft_strlen(line) > 7)
		{
			record_input_line(&line, data);
			return (-1);
		}
		if (str_is_digit(line))
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
}

int		parser(t_graph *anthill)
{
	t_parsing	data;

	if (get_ants_number(anthill, &data) != 0)
		return (-1);
	return (0);
}

int		main(void)
{
	t_graph	anthill;

	ft_bzero(&anthill, sizeof(t_graph));
	if (parser(&anthill) != 0)
	{
		ft_putendl("ERROR");
		return(0);
	}
	return (0);
}
