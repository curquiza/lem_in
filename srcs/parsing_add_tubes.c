/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_tubes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:05:56 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 19:06:04 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*get_room_with_name(char *name, t_graph *anthill)
{
	t_room	*tmp;

	tmp = anthill->rooms_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void			add_tube_to_anthill(char *line, t_graph *anthill)
{
	char	**tubes;
	t_room	*room_1;
	t_room	*room_2;

	tubes = ft_strsplit(line, '-');
	if (ft_strcmp(tubes[0], tubes[1]) == 0)
	{
		ft_tabdel(&tubes);
		return ;
	}
	room_1 = get_room_with_name(tubes[0], anthill);
	room_2 = get_room_with_name(tubes[1], anthill);
	if (room_1 && room_2)
	{
		ft_lstadd(&room_1->links, ft_lstnew(room_2, sizeof(room_2)));
		ft_lstadd(&room_2->links, ft_lstnew(room_1, sizeof(room_1)));
	}
	ft_tabdel(&tubes);
}
