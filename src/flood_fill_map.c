/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfeuer <tfeuer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:18:16 by rtorrent          #+#    #+#             */
/*   Updated: 2025/04/09 16:25:36 by tfeuer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

// 4-way queued flooding algorithm
// https://en.wikipedia.org/wiki/Flood_fill

static t_point	*dequeue_point(t_list **pqueue)
{
	t_point	*point;
	t_list	*next;

	point = NULL;
	if (*pqueue)
	{
		point = (*pqueue)->content;
		next = (*pqueue)->next;
		free(*pqueue);
		*pqueue = next;
	}
	return (point);
}

static int	enqueue_point(t_list **pqueue, t_point *point)
{
	t_point *const	new_point = malloc(sizeof(t_point));
	t_list *const	new_link = ft_lstnew(new_point);

	if (new_point && new_link)
	{
		*new_point = *point;
		ft_lstadd_back(pqueue, new_link);
		return (0);
	}
	free(new_point);
	free(new_link);
	return (1);
}

static int	fill_and_enqueue(char *empty, t_list **pqueue, t_point *point)
{
	*empty = WALL;
	if (enqueue_point(pqueue, &(t_point){point->x, point->y - 1})
		|| enqueue_point(pqueue, &(t_point){point->x - 1, point->y})
		|| enqueue_point(pqueue, &(t_point){point->x + 1, point->y})
		|| enqueue_point(pqueue, &(t_point){point->x, point->y + 1}))
		return (-2);
	return (0);
}

static int	find_idx(int rows, int cols, t_point *point)
{
	if (point->y < 0 || point->y >= rows || point->x < 0 || point->x >= cols)
		return (-1);
	return (point->y * cols + point->x);
}

void	flood_fill_map(t_game *gme, char *dup_map)
{
	t_list		*queue;
	t_point		*pt;
	int			idx;

	queue = NULL;
	idx = 0;
	if (!dup_map || enqueue_point(&queue,
			&(t_point){(int)gme->player.pos.x, (int)gme->player.pos.y}))
		idx = -2;
	while (queue && idx >= 0)
	{
		pt = dequeue_point(&queue);
		idx = find_idx(gme->data->map_data.rows, gme->data->map_data.cols, pt);
		if (idx == -1 || dup_map[idx] == SPACE)
			idx = -1;
		else if (dup_map[idx] == EMPTY)
			idx = fill_and_enqueue(&dup_map[idx], &queue, pt);
		free(pt);
	}
	free(dup_map);
	ft_lstclear(&queue, free);
	if (idx == -1)
		clean_nicely(gme, "Non-closed map");
	if (idx == -2)
		clean_nicely(gme, "Out of memory");
}
