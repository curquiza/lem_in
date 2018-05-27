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

static void	ft_del_room(t_room **room)
{
	ft_strdel(&(*room)->name);
	ft_bzero(*room, sizeof(*room));
	free(*room);
	*room = NULL;
}

static void	ft_del_rooms_array(t_room ***tab, int rooms_nb)
{
	int		i;

	if (!tab || !(*tab))
		return ;
	i = 0;
	while (i < rooms_nb)
	{
		ft_del_room(&(*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void		del_anthill(t_graph *anthill)
{
	ft_del_adj_matrix(&anthill->adj_matrix, anthill->rooms_nb);
	ft_del_rooms_array(&anthill->rooms_array, anthill->rooms_nb);
	ft_bzero(anthill, sizeof(*anthill));
}
