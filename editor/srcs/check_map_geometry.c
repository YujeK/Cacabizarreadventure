/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_geometry.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamir-k <asamir-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 02:03:20 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 23:03:12 by asamir-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int	geometry_is_valid(t_map map)
{
	if (!all_sectors_are_convex(map))
		return (0);
	if (there_are_intersections(map))
		return (0);
	if (player_outside(map))
		return (0);
	if (sprite_outside(map))
		return (0);
	return (1);
}
