/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:49:55 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/05 19:03:57 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector *fill_sectors(t_sector *sectors, char *str, int *c, t_vector *vertex)
{
	int i;
	int f;
	int part;
	int v;
	int save;
	int save2;
	int n;

	n = 0;
	f = 0;
	save = 0;
	save2 = 0;
	i = 0;
	part = 0;
	v = count_vertex(str) - 1;
	sectors[*c].npoints = v;
	sectors[*c].vertex = (t_vector*)malloc(sizeof(t_vector) * v + 1);
	sectors[*c].neighbors = (signed char*)malloc(sizeof(signed char) * v + 10);
	while (str[i])
	{
		while (str[i] && (str[i] < '0' || str[i] > '9'))
			i++;
		sectors[*c].floor = ft_iatof(str, i);
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		sectors[*c].ceil = ft_iatof(str, ++i);
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		save2 = i;
		while (str[i] && str[i] != 'c')
			i++;
		i--;
		while (str[i] && (str[i] < '0' || str[i] > '9'))
			i--;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i--;
		save = ++i;
		sectors[*c].vertex[n] = vertex[ft_iatoi(str, i)];
		n++;
		while (i != save2)
			i--;
		while (str[++i] != 'c')
		{
			sectors[*c].vertex[n] = vertex[ft_iatoi(str, i)];
			while (str[i] && str[i] >= '0' && str[i] <= '9')
				i++;
			n++;
		}
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] && (str[i] < '0' || str[i] > '9') && str[i] != '-')
			i++;
		while(str[i])
		{
			sectors[*c].neighbors[f] = ft_iatoi(str, i);
			while(str[i] && ((str[i] >= '0' && str[i] <= '9') || str[i] == '-'))
				i++;
			i++;
			f++;
		}
	}
	return (sectors);
}

t_sector	*Load_sectors(char **map, unsigned int *NumSectors, t_vector *vertex)
{
	t_sector *sectors;
	int i;
	int j;
	int t;
	int c;
	int st;

	c = 0;
	j = 0;
	i = 0;
	st = 0;
	t = ft_tablen(map);
	while(i < t)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 's')
			{
				st++;
			}
			j++;
		}
		i++;
	}
	*NumSectors = st;
	sectors = (t_sector *)malloc(sizeof(t_sector) * st);
	i = 0;
	while(i < t)
	{
		if(map[i][1] == 's')
		{
			sectors = fill_sectors(sectors, map[i], &c, vertex);
			c++;
		}
		i++;
	}
	return(sectors);
}
