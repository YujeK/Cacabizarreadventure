/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smerelo <smerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 23:49:55 by asamir-k          #+#    #+#             */
/*   Updated: 2019/05/08 06:37:22 by smerelo          ###   ########.fr       */
/*   Updated: 2019/05/08 07:34:10 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_sector	*fill_sectors(t_sector *sectors, char *str, int *c, t_vector *vertex)
t_fls2		fill_sectors2(char *str, t_fls2 b, t_sector *sectors, int *c)
{
	while (str[b.i] && (str[b.i] < '0' || str[b.i] > '9'))
		b.i++;
	sectors[*c].floor = ft_iatof(str, b.i);
	while (str[b.i] && str[b.i] >= '0' && str[b.i] <= '9')
		b.i++;
	sectors[*c].ceil = ft_iatof(str, ++b.i);
	while (str[b.i] && str[b.i] >= '0' && str[b.i] <= '9')
		b.i++;
	b.save2 = b.i;
	while (str[b.i] && str[b.i] != 'c')
		b.i++;
	b.i--;
	while (str[b.i] && (str[b.i] < '0' || str[b.i] > '9'))
		b.i--;
	while (str[b.i] && str[b.i] >= '0' && str[b.i] <= '9')
		b.i--;
	return (b);
}

	n = 0;
	f = 0;
	save = 0;
	save2 = 0;
	i = 0;
	part = 0;
	v = count_vertex(str);
	sectors[*c].npoints = v - 1;
	if (v < 4)
		exit(EXIT_FAILURE);
	if (!(sectors[*c].vertex = (t_vector*)malloc(sizeof(t_vector) * v + 100)))
		exit(EXIT_FAILURE);
	if (!(sectors[*c].neighbors = (signed char*)
		malloc(sizeof(signed char) * v + 10)))
		exit(EXIT_FAILURE);
	while (str[i])
t_fls2		fill_sectors3(char *str, t_fls2 b, t_sector *sectors, int *c)
{
	while (str[b.i] && str[b.i] >= '0' && str[b.i] <= '9')
		b.i++;
	while (str[b.i] && (str[b.i] < '0' ||
				str[b.i] > '9') && str[b.i] != '-')
		b.i++;
	while (str[b.i])
	{
		sectors[*c].neighbors[b.f] = ft_iatoi(str, b.i);
		while (str[b.i] && ((str[b.i]
						>= '0' && str[b.i] <= '9') || str[b.i] == '-'))
			b.i++;
		b.i++;
		b.f++;
	}
	return (b);
}

t_sector	*fill_sectors(t_sector *sectors, char *str,
		int *c, t_vector *vertex)
{
	t_fls2 b;

	b = init_fill_sectors(str, b, sectors, c);
	while (str[b.i])
	{
		b = fill_sectors2(str, b, sectors, c);
		b.save = ++b.i;
		sectors[*c].vertex[b.n] = vertex[ft_iatoi(str, b.i)];
		b.n++;
		while (b.i != b.save2)
			b.i--;
		while (str[++b.i] != 'c')
		{
			sectors[*c].vertex[b.n] = vertex[ft_iatoi(str, b.i)];
			while (str[b.i] && str[b.i] >= '0' && str[b.i] <= '9')
				b.i++;
			b.n++;
		}
		while (str[i] && str[i] >= '0' && str[i] <= '9')
			i++;
		while (str[i] && (str[i] < '0' || str[i] > '9') && str[i] != '-')
			i++;
		while (str[i])
		b = fill_sectors3(str, b, sectors, c);
	}
	return (sectors);
}

void		load_sectors2(char **map, unsigned int
		*numsectors, t_vector *vertex, t_lsect *b)
{
	b->st = 0;
	b->i = 0;
	while (b->i < b->t)
	{
		if (map[b->i][1] == 's')
		{
			sectors[*c].neighbors[f] = ft_iatoi(str, i);
			while (str[i] && ((str[i]
			>= '0' && str[i] <= '9') || str[i] == '-'))
				i++;
			i++;
			f++;
			b->st = 1;
			b->sect = fill_sectors(b->sect, map[b->i], &b->c, vertex);
			b->c++;
		}
		b->i++;
	}
	if (!b->st)
		exit(EXIT_FAILURE);
}


void	load_sectors2(char **map, unsigned int
	*numsectors, t_vector *vertex, t_lsect *b)
t_sector	*load_sectors(char **map, unsigned int *numsectors,
		t_vector *vertex)
{
	b->st = 0;
	b->i = 0;
	while (b->i < b->t)
	t_lsect		b;

	b.c = 0;
	b.j = 0;
	b.i = 0;
	b.st = 0;
	b.t = ft_tablen(map);
	while (b.i < b.t)
	{
		if (map[b->i][1] == 's')
		b.j = 0;
		while (map[b.i][b.j])
		{
			b->st = 1;
			b->sect = fill_sectors(b->sect, map[b->i], &b->c, vertex);
			b->c++;
			if (map[b.i][b.j] == 's')
			{
				b.st++;
			}
			b.j++;
		}
		b->i++;
		b.i++;
	}
	if (!b->st)
		exit(EXIT_FAILURE);
}


t_sector	*load_sectors(char **map, unsigned int *numsectors, t_vector *vertex)
{
	t_lsect		b;

	b.c = 0;
	b.j = 0;
	b.i = 0;
	b.st = 0;
	b.t = ft_tablen(map);
	while (b.i < b.t)
	{
		b.j = 0;
		while (map[b.i][b.j])
		{
			if (map[b.i][b.j] == 's')
			{
				b.st++;
			}
			b.j++;
		}
		b.i++;
	}
	*numsectors = b.st;
	b.sect = (t_sector *)malloc(sizeof(t_sector) * b.st);
	load_sectors2(map, numsectors, vertex, &b);
	return (b.sect);
	*numsectors = b.st;
	b.sect = (t_sector *)malloc(sizeof(t_sector) * b.st);
	load_sectors2(map, numsectors, vertex, &b);
	return (b.sect);
}
