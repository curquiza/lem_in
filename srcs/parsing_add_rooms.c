/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_add_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 19:03:22 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 19:03:40 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_room_lstadd_back(t_room **alst, t_room *new, t_room *last)
{
	t_room	*tmp;

	if (alst == NULL)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
		last->next = new;
}

static t_room	*ft_room_lstnew(char *name, int special_room, int index)
{
	t_room		*new;

	new = ft_memalloc(sizeof(*new));
	new->name = ft_strdup(name);
	new->special_room = special_room;
	new->id = index;
	new->next = NULL;
	return (new);
}

void			add_room_to_anthill(char *line, t_graph *anthill,
									t_parsing *data, int special_room)
{
	char	*name;
	char	**infos;
	t_room	*new;

	infos = ft_strsplit(line, ' ');
	name = infos[0];
	new = ft_room_lstnew(name, special_room, anthill->rooms_nb);
	ft_room_lstadd_back(&anthill->rooms_list, new, data->last_room);
	data->last_room = new;
	anthill->rooms_nb += 1;
	if (special_room == END)
		data->end = 1;
	else if (special_room == START)
		data->start = 1;
	ft_tabdel(&infos);
}
