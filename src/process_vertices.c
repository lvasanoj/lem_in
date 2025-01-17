/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_vertices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:35:22 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/17 15:47:19 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** vertex info is given in the form "id coord_x coord_y" followed by a newline.
** vertex_parse() splits the three attributes into their own strings, validates
** each one and stores them into the hash table.
**
** @str: current input line string
** @v: deteremines whether str contains source (0), sink (1) or intermediate (2)
** 	vertex info
*/
static int	vertex_parse(t_hashtab *ht, char *str, t_lem *lem, int v)
{
	char	**arr;

	if (!str)
		return (-1);
	arr = ft_strsplit(str, ' ');
	if (ft_arrlen((void **)arr) != 3)
		return (-1);
	if (arr[0][0] == 'L' || arr[0][0] == '#' || \
	!ft_digits_only(arr[1]) || !ft_digits_only(arr[2]))
		return (-1);
	set(ht, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
	if (v == 1)
		lem->sink = get(ht, arr[0]);
	else if (v == 0)
		lem->source = get(ht, arr[0]);
	ft_liberator(4, &arr[0], &arr[1], &arr[2], &arr[3]);
	free(arr);
	return (0);
}

/*
** source and sink are denoted in a preceding line by "##start" or "##end".
** if the main loop in get_vertices() encounters a line that starts with a '#',
** check_command() will check which command it is and store the following line
** accordingly to struct t_lem. lines with a comment or an invalid command are
** skipped.
*/
static t_input	*check_command(t_input *input, t_hashtab *ht, t_lem *lem)
{
	char	*str;
	char	**arr;
	int		i;

	str = input->line;
	arr = NULL;
	i = 0;
	if (ft_strequ(str, "##start") && lem->source == NULL)
	{
		input = input->next;
		if (vertex_parse(ht, input->line, lem, 0) < 0)
			return (NULL);
	}
	else if (ft_strequ(str, "##end") && lem->sink == NULL)
	{
		input = input->next;
		if (vertex_parse(ht, input->line, lem, 1) < 0)
			return (NULL);
	}
	else if ((ft_strequ(str, "##end") && lem->sink != NULL) || \
	(ft_strequ(str, "##start") && lem->source != NULL))
		return (NULL);
	else
		lem->vertices--;
	return (input->next);
}

/*
** loop through input lines until a line with a '-' (dash) is encountered.
** the lines until that point should contain all vertex names, their coordinates
** and identify source and sink vertices. if both source and sink weren't found,
** the program will exit and return error.
**
** @input: pointer to list of instructions
** @ht: pointer to hash table of vertices
** @lem: pointer to a general runtime info struct
*/
t_input	*get_vertices(t_input *input, t_hashtab *ht, t_lem *lem)
{
	while (1)
	{
		if (!input)
			return (NULL);
		if (input->line[0] == '#')
		{
			input = check_command(input, ht, lem);
			if (!input)
				return (NULL);
		}
		else if (ft_strchr(input->line, '-'))
			break ;
		else
		{
			if (vertex_parse(ht, input->line, lem, 2) < 0)
				return (NULL);
			input = input->next;
		}
		lem->vertices += 1;
	}
	if (lem->source != NULL && lem->sink != NULL)
		return (input);
	else
		return (NULL);
}
