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
	char	*input;
	int		start;
	int		end;
	int		rooms_done;
}				t_parsing;

int		is_start_command(char *line);
int		is_end_command(char *line);
int		is_valid_command(char *line);
int		is_comment(char *line);
int		str_is_digit(char *str);

void	record_input_line(char **line, t_parsing *data);
int		get_ants_number(t_graph *anthill, t_parsing *data);
int		parser(t_graph *anthill);

#endif
