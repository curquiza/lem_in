#include "lem-in.h"

void	ft_put_adj_matrix(int **tab, t_graph *anthill)
{
	int		i;
	int		j;

	i = 0;
	while (i < anthill->rooms_nb)
	{
		j = 0;
		while (j < anthill->rooms_nb)
		{
			ft_putnbr(tab[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putendl("");
		i++;
	}
}

void	ft_put_all_rooms(t_room **rooms, t_graph *anthill)
{
	int		i;

	i = 0;
	if (!rooms)
	{
		ft_putendl("no room");
		return;
	}
	while (i < anthill->rooms_nb)
	{
		ft_putstr("id : ");
		ft_putnbr_endl(rooms[i]->id);
		ft_putstr("name : ");
		ft_putendl(rooms[i]->name);
		ft_putstr("special room : ");
		ft_putchar(rooms[i]->special_room ? rooms[i]->special_room : '0');
		ft_putendl("");
		ft_putstr("weight : ");
		ft_putnbr_endl(rooms[i]->weight);
		ft_putendl("");
		i++;
	}
}

int		main(void)
{
	t_graph	anthill;
	int		ret;

	ret = 0;
	ft_bzero(&anthill, sizeof(t_graph));
	if (parser(&anthill) != 0)
	{
		ft_putendl_fd("ERROR", 2);
		ret = 1;
	}
	else
		algo(&anthill);
	del_anthill(&anthill);
	// while(1);
	return (ret);
}
