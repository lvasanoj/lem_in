/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/31 23:01:03 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define HT_SIZE 10000
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/*
** ants: nbr of ants we have to transport through the graph
** vertices: nbr of vertices in the graph
** edges: nbr of edges in the graph		¡¡¡NOTE!!! number useful at any point?
** max_flow: nbr of ants we can send through the graph at once
** source: name/id of the source vertex
** sink: name/id of the sink vertex
*/
typedef struct s_lem
{
	int		ants;
	int		vertices;
	int		edges;
	int		max_flow;
	char	*source;
	char	*sink;
}	t_lem;

/*
** linked list for the program's input, containing the data for constructing
** the graph
*/
typedef struct s_input
{
	char			*line;
	struct s_input	*next;
}	t_input;

/*
** id: name of the vertex
** x, y: coordinates of the vertex (used only for visualizer)
** visited: corresponding value for each bfs iteration
** edge: a pointer to the struct t_list, a list of outgoing edges.
** next: a pointer to another t_vertex whose id might have the same
** 	hashed value as the one being examined
*/
typedef struct s_vertex
{
	char			*id;
	int				x;
	int				y;
	int				visited;
	struct s_edge	*edge;
	struct s_vertex	*next;
}	t_vertex;

/*
** src: name/id of the edge's source vertex
** dst: name/id of the edge's destination vertex
** fwd_cap & rev_cap: forward and backward capacity of the edge, respectively
** next: a pointer to the next edge that has the same source vertex
*/
typedef struct s_edge
{
	char			*src;
	char			*to;
	int				fwd_cap;
	struct s_edge	*next;
}	t_edge;

/*
** path: head of a path found in by the breadth-first search algorithm
** next: pointer to the next route
*/
typedef struct s_route
{
	int				i;
	char			**path;
	struct s_route	*next;
}	t_route;

/*
** "hash table", aka an array of pointers to vertices
*/
typedef struct s_index
{
	struct s_vertex	**vertices;
}	t_index;

t_lem		*init_lem(void);
t_index		*init_index(void);
t_vertex	*new_vertex(const char *key, const int x, const int y);
t_edge		*new_edge(const char *src, const char *dst);
void		set(t_index *index, const char *key, const int x, const int y);
t_vertex	*get(t_index *index, const char *key);
int			parse_input(t_input *input, t_index *index, t_lem *lem);
int			get_edges(t_input *input, t_index *index);
t_route		*edm_karp(t_index *index, t_lem *lem);
char		**bfs(t_index *index, t_lem *lem, char **queue, t_route *route);
char		**wipe_array(char **arr, const int size, const char *source);
char		*pop_first(char ***arr);
void		arr_append(char ***arr, char *vertex);
int			is_linked(t_edge *curr, t_vertex *prev_vertex, char *sink);

#endif
