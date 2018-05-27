#include "lem-in.h"

static void	ft_del_adj_matrix(int ***tab, int rooms_nb)
{
	int		i;

	if (!tab || !(*tab))
		return ;
	i = 0;
	while (i < rooms_nb)
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

static void	ft_del_rooms_array(t_room ***tab)
{
	free(*tab);
	*tab = NULL;
}

static void	ft_del_rooms_list(t_room **alst)
{
	t_room	*current;
	t_room	*tmp;

	if (!alst)
		return ;
	current = *alst;
	while (current)
	{
		tmp = current;
		ft_strdel(&current->name);
		current = current->next;
		free(tmp);
	}
	*alst = NULL;
}

void		del_anthill(t_graph *anthill)
{
	ft_del_adj_matrix(&anthill->adj_matrix, anthill->rooms_nb);
	ft_del_rooms_list(&anthill->rooms_list);
	ft_del_rooms_array(&anthill->rooms_array);
	ft_bzero(anthill, sizeof(*anthill));
}
