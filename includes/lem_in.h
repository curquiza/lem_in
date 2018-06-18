/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:46:42 by curquiza          #+#    #+#             */
/*   Updated: 2018/06/18 18:49:25 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define START 1
# define END 2

typedef struct	s_room
{
	int				id;
	char			*name;
	int				special_room;
	int				weight;
	int				ant;
	t_list			*links;
	struct s_room	*next;
}				t_room;

typedef struct	s_graph
{
	int		ants_nb;
	int		rooms_nb;
	t_room	**rooms_array;
	t_room	*rooms_list;
	int		ants_in_end;
	int		ants_in_start;
	int		next_ant;

}				t_graph;

typedef struct	s_input
{
	char			*line;
	struct s_input	*next;
}				t_input;

typedef struct	s_parsing
{
	t_input	*input;
	t_input	*last_input;
	t_room	*last_room;
	int		start;
	int		end;
	int		rooms_reading_done;
}				t_parsing;

/*
** TOOLS
*/
bool			is_start_command(char *line);
bool			is_end_command(char *line);
bool			is_valid_command(char *line);
bool			is_comment(char *line);
bool			str_is_digit(char *str);

t_room			*get_special_room(t_graph *anthill, int special_room);

/*
** PARSING
*/
int				get_ants_number(t_graph *anthill, t_parsing *data);
bool			is_valid_room(char *line);
bool			is_valid_tube(char *line);
bool			is_valid_input(char *line, t_graph *anthill, t_parsing *data);
void			add_room_to_anthill(char *line, t_graph *anthill,
									t_parsing *data, int special_room);
void			add_tube_to_anthill(char *line, t_graph *anthill);

void			record_input_line(char **line, t_parsing *data);
void			read_end_of_inputs(t_parsing *data);
void			del_input_list(t_input **alst);

int				assign_weights(t_graph *anthill, t_parsing *data);

int				parser(t_graph *anthill);

/*
** ALGO
*/
t_room			*best_room_to_choose(t_room *current);
void			move_ant(t_room *from, t_room *dest, int ant, t_graph *anthill);
void			move_in_anthill(t_graph *anthill);
void			move_in_start_room(t_graph *anthill);
void			algo(t_graph *anthill);

/*
** DEL
*/
void			del_anthill(t_graph *anthill);

#endif
