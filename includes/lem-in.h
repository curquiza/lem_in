#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

typedef struct	s_room
{
	int		num;
	char	*name;
	int		weight;
	// int		adj_number;
}				t_room;

typedef struct	s_ant
{
	int		name;
	t_room	*room;
	// t_room	*previous_room;
}				t_ant;

typedef struct	s_graph
{
	int		ants_number;
	t_ant	**ants;
	t_room	**rooms;
	int		**adj_matrix;

}				t_graph;

#endif
