/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ants_number.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:06:38 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 19:06:43 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_ants_number(t_graph *anthill, t_parsing *data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) == 1 && line)
	{
		if (str_is_digit(line) && ft_strlen(line) < 8)
		{
			anthill->ants_nb = ft_atoi(line);
			record_input_line(&line, data);
			return (anthill->ants_nb ? 0 : -1);
		}
		else if (!is_comment(line))
		{
			record_input_line(&line, data);
			return (-1);
		}
		record_input_line(&line, data);
	}
	return (-1);
}
