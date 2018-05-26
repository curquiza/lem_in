#include "lem-in.h"

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

void	add_tube_to_anthill(char *line, t_graph *anthill)
{
	(void)line;
	(void)anthill;

	//check le nom
	//ajouter à la matrice adjacence si ok
}