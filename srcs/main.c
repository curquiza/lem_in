/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:59:32 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/19 11:20:04 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** void ft_put_rooms_list(t_room *rooms)
** {
** 	ft_putendl("--------------------");
** 	while (rooms)
** 	{
** 		ft_putstr("name: ");
** 		ft_putendl(rooms->name);
** 		ft_putstr("weight: ");
** 		ft_putnbr_endl(rooms->weight);
** 		ft_putendl("------");
** 		rooms = rooms->next;
** 	}
** 	ft_putendl("--------------------");
** }
*/

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
	else
		algo(&anthill);
	del_anthill(&anthill);
	return (ret);
}
