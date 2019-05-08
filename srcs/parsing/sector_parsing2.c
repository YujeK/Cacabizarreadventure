/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_parsing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 07:32:49 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 11:17:03 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fls2		init_fill_sectors(char *str, t_sector *sectors, int *c)
{
	t_fls2	b;

	b.n = 0;
	b.f = 0;
	b.save = 0;
	b.save2 = 0;
	b.i = 0;
	b.part = 0;
	b.v = count_vertex(str);
	sectors[*c].npoints = b.v - 1;
	if (b.v < 4)
		exit(EXIT_FAILURE);
	if (!(sectors[*c].vertex = (t_vector*)malloc(sizeof(t_vector) * b.v + 100)))
		exit(EXIT_FAILURE);
	if (!(sectors[*c].neighbors = (signed char*)
				malloc(sizeof(signed char) * b.v + 10)))
		exit(EXIT_FAILURE);
	return (b);
}
