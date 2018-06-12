#include "lem-in.h"

static t_room	*get_room_with_name(char *name, t_graph *anthill)
{
	int		i;

	i = 0;
	while (i < anthill->rooms_nb)
	{
		if (!ft_strcmp(anthill->rooms_array[i]->name, name))
			return (anthill->rooms_array[i]);
		i++;
	}
	return (NULL);
}

void		add_tube_to_anthill(char *line, t_graph *anthill)
{
	char	**tubes;
	t_room	*room_1;
	t_room	*room_2;

	tubes = ft_strsplit(line, '-');
	room_1 = get_room_with_name(tubes[0], anthill);
	room_2 = get_room_with_name(tubes[1], anthill);
	if (room_1 && room_2)
	{
		ft_lstadd_back(&room_1->links, ft_lstnew(room_2, sizeof(room_2)));
		ft_lstadd_back(&room_2->links, ft_lstnew(room_1, sizeof(room_1)));
	}
	ft_tabdel(&tubes);
}
