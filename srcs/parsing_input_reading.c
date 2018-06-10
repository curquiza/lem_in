#include "lem-in.h"

static void	input_add_back(t_input **alst, t_input *new, t_input *last)
{
	t_input	*tmp;

	if (!alst)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
		last->next = new;
}

static t_input	*input_new(char *line)
{
	t_input		*new;

	new = ft_memalloc(sizeof(*new));
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

void	del_input_list(t_input **alst)
{
	t_input	*current;
	t_input	*tmp;

	if (!alst)
		return ;
	current = *alst;
	while (current)
	{
		tmp = current;
		ft_strdel(&current->line);
		current = current->next;
		free(tmp);
	}
	*alst = NULL;
}

void	record_input_line(char **line, t_parsing *data)
{
	t_input	*new;

	new = input_new(*line);
	input_add_back(&data->input, new, data->last_input);
	data->last_input = new;
	ft_strdel(line);
}

void 	read_end_of_inputs(t_parsing *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == 1 && line)
		record_input_line(&line, data);
}
