/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:49:55 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/05 07:38:22 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector *fill_sectors(t_sector *sectors, char *str, int *c, t_vector *vertex)
{
	int i;
	int f;
	int part;
	int v;
	int t;
	int n;

	n = 0;
	f = 0;
	t = 1;
	i = 0;
	part = 0;
	v = count_vertex(str);
	sectors[*c].npoints = v;
	sectors[*c].vertex = (t_vector*)malloc(sizeof(t_vector) * v + 1);
	sectors[*c].neighbors = (signed char*)malloc(sizeof(signed char) * v + 1);
	while (str[i])
	{
		if (part == 0 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sectors[*c].floor = ft_iatof(str, i);
			part++;
		}
		else if (part == 1 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sectors[*c].ceil = ft_iatof(str, i);
			part++;
		}
		else if (part == 2 && t < v + 1 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sectors[*c].vertex[t] = vertex[(int)ft_iatof(str, i)];
			t++;
		}
		else if (t > v && (str[i] == '-' || (str[i] >= '0' && str[i] <= '9')) && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			sectors[*c].neighbors[n] = (unsigned char)ft_iatof(str, i);
			n++;
		}
		i++;
	}
	sectors[*c].vertex[0] = sectors[*c].vertex[t - 1];
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
