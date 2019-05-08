/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:47:49 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 11:15:40 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vector	*fill_vertex2(t_lvert *b, char *str, t_vector *vert, int *c)
{
	while (str[++b->i])
	{
		if (str[b->i] >= '0' && str[b->i] <= '9'
			&& (str[b->i - 1] == ' ' || str[b->i - 1] == '\t'))
		{
			vert[*c].x = ft_iatof(str, b->i) / 10;
			*c += 1;
			while ((str[b->i] >= '0' && str[b->i] <= '9') || str[b->i] == '.')
				b->i++;
		}
	}
	return (vert);
}

t_vector	*fill_vertex(t_vector *vert, char *str, int *c)
{
	t_lvert b;

	b.t = *c - 1;
	b.y = -1;
	b.i = -1;
	b.v = 0;
	while (str[++b.i])
	{
		if (str[b.i] >= '0' && str[b.i] <= '9' && b.y == -1)
			b.y = b.i;
		if (str[b.i] && str[b.i] >= '0' && str[b.i] <= '9'
		&& (str[b.i + 1] == ' ' || str[b.i + 1] == '\0'
		|| str[b.i + 1] == '\t'))
			b.v++;
	}
	while (++b.t < b.v - 1 + *c)
		vert[b.t].y = ft_iatof(str, b.y) / 10;
	b.i = b.y;
	vert = fill_vertex2(&b, str, vert, c);
	return (vert);
}

int			count_vertex(char *str)
{
	int i;
	int c;

	c = 0;
	i = 0;
	while (str[i] < '0' || str[i] > '9')
		i++;
	while (str[i] >= '0' && str[i] >= '9')
		i++;
	i++;
	while (str[i] >= '0' && str[i] >= '9')
		i++;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			break ;
		if (str[i] >= '0' && str[i] <= '9'
			&& (str[i - 1] == ' ' || str[i - 1] == '\t'))
			c++;
	}
	if (c == 0)
		exit(EXIT_FAILURE);
	return (c);
}

void		load_vertex2(t_lvert *b, char **map)
{
	if (b->vt == 0)
		exit(EXIT_FAILURE);
	b->i = -1;
	b->vertex = (t_vector*)malloc(sizeof(t_vector) * b->vt);
	while (++b->i < b->vt)
	{
		b->vertex[b->i].x = 0;
		b->vertex[b->i].y = 0;
	}
	b->i = -1;
	while (++b->i < b->t - 3)
	{
		if (map[b->i][0] == 'v')
			b->vertex = fill_vertex(b->vertex, map[b->i], &b->c);
		else if (map[b->i][1] == 'v')
			b->vertex = fill_vertex(b->vertex, map[b->i], &b->c);
		else if (map[b->i][2] == 'v')
			b->vertex = fill_vertex(b->vertex, map[b->i], &b->c);
	}
}

t_vector	*load_vertex(char **map)
{
	t_lvert b;

	b.i = -1;
	b.c = 0;
	b.vt = 0;
	b.t = (int)ft_tablen(map);
	while (++b.i < b.t - 3)
	{
		b.j = -1;
		while (map[b.i] && ++b.j < (int)ft_strlen(map[b.i]))
		{
			if (map[b.i][b.j] && (map[b.i][0] == 'v' || map[b.i][1] == 'v'
			|| map[b.i][2] == 'v') && map[b.i][b.j]
			>= '0' && map[b.i][b.j] <= '9'
			&& (map[b.i][b.j - 1] == ' ' || map[b.i][b.j - 1] == '\t'))
				b.vt++;
		}
	}
	load_vertex2(&b, map);
	return (b.vertex);
}
