#include "lem-in.h"

static void		ft_room_lstadd_back(t_room **alst, t_room *new)
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

static t_room	*ft_room_lstnew(char *name, int special_room, int index)
{
	t_room		*new;

	new = ft_memalloc(sizeof(*new));
	new->name = ft_strdup(name);
	new->special_room = special_room;
	new->id = index;
	new->next = NULL;
	return (new);
}

void			add_room_to_anthill(char *line, t_graph *anthill,
									t_parsing *data, int special_room)
{
	char	*name;
	char 	**infos;

	infos = ft_strsplit(line, ' ');
	name = infos[0];
	ft_room_lstadd_back(&anthill->rooms_list, ft_room_lstnew(name, special_room,
															anthill->rooms_nb));
	anthill->rooms_nb += 1;
	if (special_room == END)
		data->end = 1;
	else if (special_room == START)
		data->start = 1;
	ft_tabdel(&infos);
}
