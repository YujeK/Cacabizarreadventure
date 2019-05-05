/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:47:49 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/05 14:40:13 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vector	*fill_vertex(t_vector *vert, char *str, int *c)
{
	int i;
	int v;
	int y;
	int t;

	t = *c;
	y = -1;
	i = 0;
	v = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && y == -1)
			y = i;
		if (str[i] && str[i] >= '0' && str[i] <= '9' && (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '\t'))
			v++;
		i++;
	}
	i = 0;
	while (t < v - 1 + *c)
	{
		vert[t].y = ft_iatof(str, y) / 10;
		t++;
	}
	i = y + 1;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			vert[*c].x  = ft_iatof(str, i) / 10;
			*c += 1;
			while((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
				i++;
		}
		i++;
	}
	return (vert);
}

int 	count_vertex(char *str)
{
	int i;
	int c;

	c = 0;
	i = 0;

	while(str[i] < '0' || str[i] > '9')
		i++;
	while(str[i] >= '0' && str[i] >= '9')
		i++;
	i++;
	while(str[i] >= '0' && str[i] >= '9')
		i++;
	i++;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			break;
		if(str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			c++;
		}
		i++;
	}
	return(c);
}

t_vector	*Load_vertex(char **map)
{
	size_t i;
	int j;
	int v;
	int vt;
	int st;
	int s;
	int c;
	size_t t;
	t_vector *vertex;

	i = 0;
	v = 0;
	c = 0;
	s = 0;
	vt = 0;
	st = 0;
	t = ft_tablen(map);
	while (i < t - 3)
	{
		j= 0;
		while(map[i][j])
		{
			if (map[i][j] && (map[i][0] == 'v' || map[i][1] == 'v' || map[i][2] == 'v') && map[i][j] >= '0'
			&& map[i][j] <= '9' && (map[i][j - 1] == ' ' || map[i][j - 1] == '\t'))
				vt++;
			j++;
		}
		i++;
	}
	vt = 66;
	i = 0;
	vertex = (t_vector*)malloc(sizeof(t_vector) * vt);
	while(i < vt)
	{
		vertex[i].x = 0;
		vertex[i].y = 0;
		i++;
	}
	i = 0;
	while(i < t - 3)
	{
		if (map[i][0] == 'v')
		{
			vertex = fill_vertex(vertex, map[i], &c);
		}
		else if (map[i][1] == 'v')
		{
			vertex = fill_vertex(vertex, map[i], &c);
		}
		else if (map[i][2] == 'v')
		{
			vertex = fill_vertex(vertex, map[i], &c);
		}
		i++;
	}
	i = 0;
	return (vertex);
}
