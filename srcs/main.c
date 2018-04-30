#include "lem-in.h"

int		parser(void)
{
	char	*line;
	int		ret;

	while (42)
	{
		ret = -2;
		if ((ret = get_next_line(0, &line)) != 1)
		{
			ft_strdel(&line);
			return (0);
		}
		else
		{
			ft_putendl(line);
			ft_strdel(&line);
		}
	}
	return (0);
}

int		main(void)
{
	if (parser() != 0)
		return(0);
	return (0);
}
