#include "lem-in.h"

int		main(void)
{
	t_graph	anthill;

	ft_bzero(&anthill, sizeof(t_graph));
	if (parser(&anthill) != 0)
	{
		ft_putendl_fd("ERROR", 2);
		return(1);
	}
	return (0);
}
