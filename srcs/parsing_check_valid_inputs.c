/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_valid_inputs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:08:56 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 19:09:00 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		is_valid_tube(char *line)
{
	char	*tmp;

	if (!line
		|| *line == '-'
		|| ft_strchr(line, ' ')
		|| !(tmp = ft_strchr(line, '-'))
		|| tmp != ft_strrchr(line, '-')
		|| !*(tmp + 1))
		return (false);
	return (true);
}

bool		is_valid_room(char *line)
{
	char	*tmp;

	if (!line || line[0] == 'L' || ft_strchr(line, '-'))
		return (false);
	if (!(tmp = ft_strchr(line, ' ')))
		return (false);
	line = tmp + 1;
	while (*line && *line != ' ')
	{
		if (!ft_isdigit(*line))
			return (false);
		line++;
	}
	if (!*line)
		return (false);
	line++;
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (false);
		line++;
	}
	return (true);
}

bool		is_valid_input(char *line, t_parsing *data)
{
	if (data->rooms_reading_done == 0)
	{
		if (is_valid_room(line))
			return (true);
		else if (is_valid_tube(line))
		{
			data->rooms_reading_done = 1;
			return (true);
		}
		return (false);
	}
	else
		return (is_valid_tube(line));
}
