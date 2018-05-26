#include "lem-in.h"

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

void	ft_room_lstadd_back(t_room **alst, t_room *new)
{
	t_room	*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_room	*ft_room_lstnew(char *name, int special_room, int index)
{
	t_room		*new;

	new = ft_memalloc(sizeof(*new));
	new->name = ft_strdup(name);
	new->special_room = special_room;
	new->id = index;
	new->next = NULL;
	return (new);
}

void	add_room_to_anthill(char *line, t_graph *anthill, t_parsing *data, int special_room)
{
	char	*name;
	char 	**infos;

	infos = ft_strsplit(line, ' ');
	name = infos[0];
	ft_room_lstadd_back(&anthill->rooms_list, ft_room_lstnew(name, special_room, data->rooms_nb));
	data->rooms_nb += 1;
	ft_tabdel(&infos);
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