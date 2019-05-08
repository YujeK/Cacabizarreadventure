/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprite_position.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 01:29:02 by dhorvill          #+#    #+#             */
/*   Updated: 2019/05/08 07:46:23 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doome.h"

int		g_sprite_outside(t_map map)
{
	int i;

	i = -1;
	while (++i < map.sprite_g_len)
	{
		if (in_sector_full(map, map.g_sprite[i].pos) == -1)
			return (1);
	}
	return (0);
}

int		r_sprite_outside(t_map map)
{
	int i;

	i = -1;
	while (++i < map.sprite_r_len)
	{
		if (in_sector_full(map, map.r_sprite[i].pos) == -1)
			return (1);
	}
	return (0);
}

int		sprite_outside(t_map map)
{
	if (r_sprite_outside(map))
		return (1);
	if (g_sprite_outside(map))
		return (1);
	return (0);
}
