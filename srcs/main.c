#include "lem-in.h"

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
	del_anthill(&anthill);
	// while(1);
	return (ret);
}
