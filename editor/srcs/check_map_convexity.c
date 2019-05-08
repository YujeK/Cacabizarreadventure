/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_convexity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:03:11 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:45:45 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int	has_different_sign(int a, int b)
{
	if (a == 0)
		return (0);
	if (a / b < 0)
		return (1);
	return (0);
}

int	sector_is_convex(t_map map, int sector_index)
{
	int		cross_product_sign;
	t_wall	first_edge;
	t_wall	second_edge;
	int		cross_product_result;
	int		i;

	i = -1;
	while (++i < map.sector[sector_index].edges_length - 1)
	{
		first_edge = get_line_coordinates(map,
				map.sector[sector_index].edges[i]);
		second_edge = get_line_coordinates(map,
				map.sector[sector_index].edges[i + 1]);
		cross_product_result = vector_cross_product(first_edge, second_edge);
		if (i == 0)
			cross_product_sign = cross_product_result > 0 ? 1 : -1;
		if (has_different_sign(cross_product_result, cross_product_sign))
			return (0);
	}
	first_edge = get_line_coordinates(map, map.sector[sector_index].edges[i]);
	second_edge = get_line_coordinates(map, map.sector[sector_index].edges[0]);
	cross_product_result = vector_cross_product(first_edge, second_edge);
	if (has_different_sign(cross_product_result, cross_product_sign))
		return (0);
	return (1);
}

int	all_sectors_are_convex(t_map map)
{
	int i;

	i = -1;
	while (++i < map.sector_length)
	{
		if (!sector_is_convex(map, i))
			return (0);
	}
	return (1);
}
