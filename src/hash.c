/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/31 15:33:51 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_index	*init_index(void)
{
	t_index	*index;
	int		i;

	if (!(index = (t_index *)malloc(sizeof(t_index))))
		return (NULL);
	if (!(index->rooms = (t_room **)malloc(sizeof(t_room *) * SIZE)))
		return (NULL);
	i = 0;
	while (i < SIZE)
	{
		index->rooms[i] = NULL;
		i++;
	}
	return (index);
}

t_room	*new_room(const char *key, const int x, const int y)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);		// TODO: error (OOM)
	room->id = ft_strdup(key);
	room->x = x;
	room->y = y;
	room->tube = NULL;
	room->next = NULL;
	return (room);
}

int		hashof(const char *key)
{
	int	val;
	int	i;

	val = 42;
	i = 0;
	while (i < (int)ft_strlen(key))
	{
		val *= key[i] + 89;
		i++;
	}
	return (val % SIZE);
}

t_room	*get(t_index *index, char *key)
{
	int	i;

	i = hashof(key);
	while (index->rooms[i] != NULL)
	{
		if (ft_strequ(key, index->rooms[i]->id))
			return (index->rooms[i]);
		else
			index->rooms[i] = index->rooms[i]->next;
	}
	return (NULL);
}

void	set(t_index *index, const char *key, const int x, const int y)
{
	int	i;

	i = hashof(key);
	if (index->rooms[i] == NULL)
		index->rooms[i] = new_room(key, x, y);
	else
	{
		while (index->rooms[i] != NULL)
		{
			if (ft_strequ(key, index->rooms[i]->id))
			{
				index->rooms[i]->x = x;
				index->rooms[i]->y = y;
				return ;
			}
			index->rooms[i] = index->rooms[i]->next;
		}
		index->rooms[i] = new_room(key, x, y);
	}
}