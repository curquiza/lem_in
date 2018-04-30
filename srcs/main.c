#include "lem-in.h"

int		is_comment(char *line)
{
	return (line[0] == '#');
}

int		is_valid_command(char *line)
{
	return ( is_start_command(line) || is_end_command(line))
}

int		is_start_command(char *line)
{
	return (strequ(line, "##start"));
}

int		is_end_command(char *line)
{
	return (strequ(line, "##end"));
}

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
