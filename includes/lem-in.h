#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_room
{
	int				id;
	char			*name;
	int				special_room; // 'e' ou 's'
	int				weight;
	int				ant;
	struct s_room	*next;
}				t_room;

typedef struct	s_graph
{
	int		ants_nb;
	int		rooms_nb;
	t_room	**rooms_array;
	t_room	*rooms_list;
	int		**adj_matrix;

}				t_graph;

typedef struct	s_parsing
{
	char	*input;
	int		start;
	int		end;
	// int		rooms_nb;
	int		rooms_reading_done;
}				t_parsing;

/*
** TOOLS
*/
int		is_start_command(char *line);
int		is_end_command(char *line);
int		is_valid_command(char *line);
int		is_comment(char *line);
int		str_is_digit(char *str);

/*
** PARSING
*/
int		get_ants_number(t_graph *anthill, t_parsing *data);
int		is_valid_room(char *line);
int		is_valid_tube(char *line);
int		is_valid_input(char *line, t_graph *anthill, t_parsing *data);
void	add_room_to_anthill(char *line, t_graph *anthill, t_parsing *data,
							int special_room);
void	add_tube_to_anthill(char *line, t_graph *anthill);

void	record_input_line(char **line, t_parsing *data);
void 	read_end_of_inputs(t_parsing *data);

int		assign_weights(t_graph *anthill, t_parsing *data);

int		parser(t_graph *anthill);

/*
** ALGO
*/

#endif
