#include "lem-in.h"

int		is_start_command(char *line)
{
	return (ft_strequ(line, "##start"));
}

int		is_end_command(char *line)
{
	return (ft_strequ(line, "##end"));
}

int		is_valid_command(char *line)
{
	return (is_start_command(line) || is_end_command(line));
}

int		is_comment(char *line)
{
	return (line[0] == '#' && !is_valid_command(line));
}

int		str_is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}