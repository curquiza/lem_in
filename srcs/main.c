#include "lem-in.h"

int		is_comment(char *line)
{
	return (line[0] == '#');
}

int		is_valid_command(char *line)
{
	return (is_start_command(line) || is_end_command(line))
}

int		is_start_command(char *line)
{
	return (strequ(line, "##start"));
}

int		is_end_command(char *line)
{
	return (strequ(line, "##end"));
}

int		str_is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
	}
	return (1);
}

int		get_ants_number(char *line)
{
	char	*line;

	line = NULL;
	while (42)
	{
		if (get_next_line(0, &line) != 1 || !line)
		{
			ft_strdel(&line);
			return (-1);
		}
		if (is_valid_command(line))
		{
			ft_strdel(&line);
			return (-1);
		}
		if (str_is_digit(line))
		{	
			
			return (0);
		}
	}
}

int		parser(void)
{
	// char	*line;
	// int		ret;

	// while (42)
	// {
	// 	ret = -2;
	// 	if ((ret = get_next_line(0, &line)) != 1)
	// 	{
	// 		ft_strdel(&line);
	// 		return (0);
	// 	}
	// 	else
	// 	{
	// 		ft_putendl(line);
	// 		ft_strdel(&line);
	// 	}
	// }
	return (0);
}

int		main(void)
{
	if (parser() != 0)
		return(0);
	return (0);
}
