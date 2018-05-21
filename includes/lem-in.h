#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

// typedef struct	s_ant
// {
// 	int		id;
// 	t_room	*room;
// }				t_ant;

typedef struct	s_room
{
	int						id;
	char					*name;
	int						weight;
	int						ant;
	// t_ant					*ant;
	struct s_room	*next;
}				t_room;

typedef struct	s_graph
{
	int			ants_nb;
	// t_ant		**ants;
	t_room	**rooms_array;
	t_room	*rooms_list;
	int			**adj_matrix;

}								t_graph;

typedef struct	s_draft
{
	char						*content;
	struct s_draft	*next;
}				t_draft;

typedef struct	s_parsing
{
	// t_draft	*input;
	char	*input;
	// t_draft	*rooms_draft;
	int		start;
	int		end;
}				t_parsing;

#endif
