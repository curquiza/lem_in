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

void 	read_end_of_inputs(t_parsing *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) != 1 && line)
		record_input_line(&line, data);
}

//fonction pour continuer de lire
