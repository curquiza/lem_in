#include "lem_in.h"

bool	is_start_command(char *line)
{
	return (ft_strequ(line, "##start"));
}

bool	is_end_command(char *line)
{
	return (ft_strequ(line, "##end"));
}

bool	is_valid_command(char *line)
{
	return (is_start_command(line) || is_end_command(line));
}

bool	is_comment(char *line)
{
	return (line[0] == '#' && !is_valid_command(line));
}

bool	str_is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
